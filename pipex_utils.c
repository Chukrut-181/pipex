/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:54:21 by igchurru          #+#    #+#             */
/*   Updated: 2024/09/25 10:19:41 by igchurru         ###   ########.fr       */
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

/* void	set_to_zero(t_pipedata *pipedata)
{
	pipedata->fd_input = 0;
	pipedata->fd_output = 0 ;
	pipedata->pipedes[2] = NULL;
	pipedata->valid_path = false;
	pipedata->env_vars = NULL;
} */
