/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:54:21 by igchurru          #+#    #+#             */
/*   Updated: 2024/09/24 12:09:22 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_free_exit(char *str, t_pipedata *pipedata)
{
	ft_putstr_fd(str, 2);
	free_matrix(pipedata->env_vars);
	exit(-1);
}

void	free_matrix(char **to_free)
{
	int	i;

	i = 0;
	while (to_free[i])
	{
		free(to_free[i]);
		i++;
	}
	free(to_free);
}

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
		perror ("Cannot open infile");
	close(infile);
	outfile = open(argv[4], O_WRONLY);
	if (outfile < 0)
		perror ("Cannot open outfile");
	close(outfile);
}

/* void	set_to_zero(t_pipedata *pipedata)
{
	pipedata->fd_input = 0;
	pipedata->fd_output = 0 ;
	pipedata->pipedes[2] = NULL;
	pipedata->valid_path = false;
	pipedata->env_vars = NULL;
} */
