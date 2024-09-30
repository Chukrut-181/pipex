/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:54:21 by igchurru          #+#    #+#             */
/*   Updated: 2024/09/30 13:28:39 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* get_path extracts from the env variables the one that begins with "PATH=",
splits it at every ":", and fills pipedata->env_vars. */
void	get_path(t_pipedata *pipedata, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 5))
			pipedata->env_vars = ft_split(env[i] + 5, ':');
		i++;
	}
}

/* Opens and closes the infile and outfile with their respective permissions
so as to check that they can be reached and worked with.*/
void	checkfiles(char **argv)
{
	int	infile;
	int	outfile;

	infile = open(argv[1], O_RDONLY);
	if (infile < 0)
		error_exit("Cannot open infile\n");
	close(infile);
	outfile = open(argv[4], O_WRONLY);
	if (outfile < 0)
		error_exit ("Cannot open outfile\n");
	close(outfile);
}

/* act_execve prepares the command to be run by execve. It splits the argv
and the creates a path to execute it. If accesable, it is marked as "true"
in the pipedata. If no valid path to executable is found, everything is
freed and program stops with -1. */
void	act_execve(char *argv, t_pipedata *pipedata, char **env)
{
	int		i;
	char	**command_and_flags;
	char	*path_to_exec;
	char	*aux;

	i = 0;
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
