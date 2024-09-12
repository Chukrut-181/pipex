/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 10:11:36 by igchurru          #+#    #+#             */
/*   Updated: 2024/09/11 13:37:22 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* Parent process acts after child process is completed. */
void	act_parent(t_pipedata *pipedata, char **argv, char **env)
{
	pipedata->fd_output = open(argv[4], O_CREAT, O_TRUNC, O_WRONLY);
	if (pipedata->fd_output < 0)
		perror("Error opening or creating outfile");
	if (dup2(pipedata->pipedes[0], STDIN_FILENO))
		perror("Dup2 error");
	if (dup2(pipedata->fd_output, STDOUT_FILENO));
		perror("Dup2 error");
	close(pipedata->fd_output);
	close(pipedata->pipedes[0]);
	close(pipedata->pipedes[1]);
	// act execve second command argv[3]
}

/* Child process acts now.  */
void	act_child(t_pipedata *pipedata, char **argv, char **env)
{
	pipedata->fd_input = open(argv[1], O_RDONLY);
	if (pipedata->fd_input < 0)
		perror("Error opening infile");
	if (dup2(pipedata->pipedes[1], STDOUT_FILENO) < 0)
		perror("Dup2 error");
	if (dup2(pipedata->fd_input, STDIN_FILENO) < 0)
		perror ("Dup2 error");
	close(pipedata->fd_input);
	close(pipedata->pipedes[0]);
	close(pipedata->pipedes[1]);
	// act execve first command argv[2]
}

void	pipex(t_pipedata *pipedata, char **argv, char **env)
{
	pid_t	pid;
	if (pipe(pipedata->pipedes) != 0)
		perror("Error creating pipe");
	fork();
	if (pid == 0)
	{
		act_child(pipedata, argv, env);
	}
	else if (pid < 0)
	{
		//free allocs
		//perror("Error creating child")
	}
	if (pid > 0 )
	{
		//act parent
	}
}

int	main(int argc, char **argv, char **env)
{
	t_pipedata	pipedata;
	
	if (argc != 5)
		perror("Invalid number of arguments");
	checkfiles(argc, argv);
	set_to_zero(&pipedata);
	pipex(&pipedata, argv, env);
	return (0);
}