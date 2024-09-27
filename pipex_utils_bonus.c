/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 09:51:40 by igchurru          #+#    #+#             */
/*   Updated: 2024/09/27 11:56:13 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/* This function checks for the existence of the here_doc command. If found,
heredoc flag is set to true, limit keyword is registered, and also the number of
commands and the first command are registered. Then, a temporal file is created
to store the inpur from the terminal. */
void	check_for_heredoc(int argc, char **argv, t_pipedata *pipedata)
{
	if (!ft_strncmp(argv[1], "here_doc", 8)
		&& argc > 5 && check_file(argv[argc - 1], 'W'))
	{
		pipedata->heredoc = true;
		pipedata->limit = ft_strdup(argv[2]);
		pipedata->n_of_commands = argc -4;
		pipedata->first_command = 3;
		create_tmp(pipedata);
	}
	else if (pipedata->heredoc == false && argc > 4
		&& check_file(argv[1], 'R') && check_file(argv[argc - 1], 'W'))
	{
		pipedata->n_of_commands = argc - 3;
		pipedata->first_command = 2;
	}
}

/* Checks whether the infile and outfile can be accessed
with their corresponding permits. */
int	check_file(char *file, char c)
{
	if (c == 'R')
	{
		if (access(file, R_OK))
			error_exit("Invalid infile\n");
	}
	else if (c == 'W')
	{
		if (access(file, W_OK))
			error_exit("Invalid outfile\n");
	}
	return (1);
}

/* Create_pipes uses a while loop to create multiple pipes at once and
stores their pipedes in the data structure. */
void	create_pipes(t_pipedata *pipedata)
{
	int	i;

	i = 0;
	pipedata->pipedes = malloc(sizeof(int *) * (pipedata->n_of_commands - 1));
	while (i < pipedata->n_of_commands - 1)
	{
		pipedata->pipedes[i] = malloc(sizeof(int) * 2);
		pipe(pipedata->pipedes[i]);
		i++;
	}
}

void	close_pipe(t_pipedata *pipedata, int k)
{
	int	i;

	i = 0;
	while (i < k)
	{
		close(pipedata->pipedes[i][0]);
		close(pipedata->pipedes[i][1]);
		i++;
	}
}

void	act_execve(t_pipedata *pipedata, char *argv, char **env)
{
	int		i;
	char	**command_and_flags;
	char	*path_to_exec;
	char	*aux;

	i = 0;
	path_to_exec = NULL;
	command_and_flags = ft_split(argv, ' ');
	while (pipedata->env_vars[i])
	{
		aux = ft_strjoin(pipedata->env_vars[i++], "/");
		path_to_exec = ft_strjoin(aux, command_and_flags[0]);
		free(aux);
		if (!access(path_to_exec, F_OK))
		{
			pipedata->valid_path = true;
			break ;
		}
		else
			free(path_to_exec);
	}
	if (pipedata->valid_path == true)
		execve(path_to_exec, command_and_flags, env);
	free_matrix(command_and_flags);
	error_free_exit("Command not found\n", pipedata);
}
