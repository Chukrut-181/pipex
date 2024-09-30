/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 10:11:36 by igchurru          #+#    #+#             */
/*   Updated: 2024/09/30 13:30:02 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	act_second_child(t_pipedata *pipedata, char **argv, char **env)
{
	get_path(pipedata, env);
	pipedata->fd_output = open(argv[4], O_CREAT | O_TRUNC | O_WRONLY, 0777);
	if (pipedata->fd_output < 0)
		error_free_exit("Error opening or creating outfile\n", pipedata);
	if (dup2(pipedata->pipedes[0], STDIN_FILENO) < 0)
		error_free_exit("Dup2 error\n", pipedata);
	if (dup2(pipedata->fd_output, STDOUT_FILENO) < 0)
		error_free_exit("Dup2 error\n", pipedata);
	close(pipedata->fd_output);
	close(pipedata->pipedes[0]);
	close(pipedata->pipedes[1]);
	act_execve(argv[3], pipedata, env);
}

void	act_first_child(t_pipedata *pipedata, char **argv, char **env)
{
	get_path(pipedata, env);
	pipedata->fd_input = open(argv[1], O_RDONLY);
	if (pipedata->fd_input < 0)
		error_free_exit("Error opening infile\n", pipedata);
	if (dup2(pipedata->pipedes[1], STDOUT_FILENO) < 0)
		error_free_exit("Dup2 error\n", pipedata);
	if (dup2(pipedata->fd_input, STDIN_FILENO) < 0)
		error_free_exit ("Dup2 error\n", pipedata);
	close(pipedata->pipedes[0]);
	close(pipedata->pipedes[1]);
	close(pipedata->fd_input);
	act_execve(argv[2], pipedata, env);
}

/* pipex forks twice the main process creating two children. First child
will run while last child and parent wait. When finished, last child
will act and parent will wait. When last child is done, parent will
continue and finish. */
void	pipex(t_pipedata *pipedata, char **argv, char **env)
{
	pid_t	pid;

	if (pipe(pipedata->pipedes) != 0)
		error_free_exit("Error creating pipe\n", pipedata);
	pid = fork();
	if (pid == 0)
		act_first_child(pipedata, argv, env);
	else if (pid < 0)
		error_free_exit("Error creating first child\n", pipedata);
	wait(NULL);
	pid = fork();
	if (pid == 0)
		act_second_child(pipedata, argv, env);
	else if (pid < 0)
		error_free_exit("Error creating second child\n", pipedata);
	close(pipedata->pipedes[0]);
	close(pipedata->pipedes[1]);
	wait(NULL);
}

int	main(int argc, char **argv, char **env)
{
	t_pipedata	pipedata;

	if (argc != 5)
		error_exit("Invalid number of arguments\n");
	checkfiles(argv);
	ft_bzero(&pipedata, sizeof(t_pipedata));
	pipex(&pipedata, argv, env);
	return (0);
}
