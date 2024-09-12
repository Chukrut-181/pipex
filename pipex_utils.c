/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:54:21 by igchurru          #+#    #+#             */
/*   Updated: 2024/09/11 12:53:59 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* Opens and closes the infile and outfile with their respective permissions
so as to check that they can be reached and worked with.*/
void	checkfiles (int argc, char **argv)
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

void	set_to_zero(t_pipedata *pipedata)
{
	pipedata->fd_input = 0;
	pipedata->fd_output = 0 ;
	pipedata->pipedes[2] = NULL;
	pipedata->valid_path = false;
	pipedata->env_vars = NULL;
}
