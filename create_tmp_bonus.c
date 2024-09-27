/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tmp_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 11:54:52 by igchurru          #+#    #+#             */
/*   Updated: 2024/09/27 11:32:51 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/* If here_doc was found, this function will create a .tmp file to store the
input from the terminal untill the limiter is found. */
void	create_tmp(t_pipedata *pipedata)
{
	char	*line;
	char	*limiter;

	limiter = ft_strjoin(pipedata->limit, "\n");
	pipedata->fd_input = open(".tmp", O_CREAT | O_WRONLY | O_TRUNC, 0777);
	while (1)
	{
		line = get_one_line(0);
		if (!ft_strncmp(limiter, line, ft_strlen(limiter)))
		{
			free(limiter);
			break ;
		}
		ft_putstr_fd(line, pipedata->fd_input);
		free(line);
	}
}

/* getline will read from the terminal one char at a time and create a string
to be returned to the create_tmp function */
char	*get_one_line(int fd)
{
	char	c;
	char	*str;
	char	*temp;

	str = malloc(1 * sizeof(char));
	str[0] = 0;
	while (read(fd, &c, 1) > 0)
	{
		temp = malloc(2 * sizeof(char));
		temp[0] = c;
		temp[1] = 0;
		str = ft_strjoin(str, temp);
		free(temp);
		if (c == '\n')
			break ;
	}
	return (str);
}
