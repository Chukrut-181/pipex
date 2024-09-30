/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 09:50:16 by igchurru          #+#    #+#             */
/*   Updated: 2024/09/30 13:19:47 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/* This function controls the last process, and works the same as the first
one, except the output is redirected here to the outfile via the fd_output.
Note that, if this is a here_doc case, the outfile is not truncated but instead
it is appended to. Outfile is truncated only if this is not a here_doc case.*/
void	act_last_child(int i, t_pipedata *pipedata, char **argv, char **env)
{
	get_path(pipedata, env);
	if (pipedata->heredoc == true)
		pipedata->fd_output = open(argv[pipedata->argc_count - 1],
				O_APPEND | O_WRONLY, 0777);
	if (pipedata->heredoc == false)
		pipedata->fd_output = open(argv[pipedata->argc_count - 1],
				O_TRUNC | O_WRONLY, 0777);
	if (dup2(pipedata->pipedes[i - 1][0], STDIN_FILENO) < 0)
		error_free_exit("Dup2 error\n", pipedata);
	if (dup2(pipedata->fd_output, STDOUT_FILENO) < 0)
		error_free_exit("Dup2 error\n", pipedata);
	close_pipe(pipedata, i);
	close(pipedata->fd_output);
	act_execve(pipedata, argv[pipedata->argc_count - 2], env);
}

/* All middle processes are handled here. The previous pipex function
performs the iterations. This one connects the input and output to
the corresponding pipe, then closes it and proceeds to act_execve. */
void	act_middle_children(int i, t_pipedata *pipedata, char **argv,
			char **env)
{
	get_path(pipedata, env);
	if (dup2(pipedata->pipedes[i - 1][0], STDIN_FILENO) < 0)
		error_free_exit("Dup2 error\n", pipedata);
	if (dup2(pipedata->pipedes[i][1], STDOUT_FILENO) < 0)
		error_free_exit("Dup2 error\n", pipedata);
	close_pipe(pipedata, pipedata->n_of_commands - 1);
	act_execve(pipedata, argv[i + 2], env);
}

/* This function controls the first child process. It distinguishes if
this is or this is not a "here_doc case" and sets the input fd accordingly.
Then coneccts the output to the writing end of the first pipe, closes the
pipe and the input fd and calls to act_execve. */
void	act_first_child(t_pipedata *pipedata, char **argv, char **env)
{
	get_path(pipedata, env);
	if (pipedata->heredoc == true)
		pipedata->fd_input = open(".tmp", O_RDONLY);
	else if (pipedata->heredoc == false)
		pipedata->fd_input = open(argv[1], O_RDONLY);
	if (pipedata->fd_input < 0)
		error_free_exit("Error opening infile\n", pipedata);
	if (dup2(pipedata->pipedes[0][1], STDOUT_FILENO) < 0)
		error_free_exit("Dup2 error\n", pipedata);
	if (dup2(pipedata->fd_input, STDIN_FILENO) < 0)
		error_free_exit ("Dup2 error\n", pipedata);
	close_pipe(pipedata, pipedata->n_of_commands - 1);
	close(pipedata->fd_input);
	act_execve(pipedata, argv[pipedata->first_command], env);
}

void	pipex(t_pipedata *pipedata, int argc, char **argv, char **env)
{
	pid_t	pid;
	int		i;

	i = 0;
	while (i + pipedata->first_command < argc - 1)
	{
		pid = fork();
		if (pid == 0)
		{
			if (i == 0)
				act_first_child(pipedata, argv, env);
			else if (i + pipedata->first_command == argc - 2)
				act_last_child(i, pipedata, argv, env);
			else
				act_middle_children(i, pipedata, argv, env);
		}
		close_pipe(pipedata, i);
		waitpid(pid, NULL, 0);
		i++;
	}
	if (pipedata->heredoc == true)
		free(pipedata->limit);
	free_pipedes(pipedata);
	unlink(".tmp");
}

int	main(int argc, char **argv, char **env)
{
	t_pipedata	pipedata;

	if (argc < 5)
		error_exit("Invalid number of arguments\n");
	ft_bzero(&pipedata, sizeof(t_pipedata));
	pipedata.argc_count = argc;
	check_for_heredoc(argc, argv, &pipedata);
	create_pipes(&pipedata);
	pipex(&pipedata, argc, argv, env);
	return (0);
}
