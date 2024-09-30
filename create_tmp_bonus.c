/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tmp_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 11:54:52 by igchurru          #+#    #+#             */
/*   Updated: 2024/09/30 12:52:09 by igchurru         ###   ########.fr       */
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
	pipedata->fd_input = open(".tmp", O_CREAT | O_TRUNC | O_RDWR, 0777);
	while (true)
	{
		line = get_one_line(0);
		if (ft_strncmp(limiter, line, ft_strlen(limiter)) == 0)
		{
			free(limiter);
			break ;
		}
		ft_putstr_fd(line, pipedata->fd_input);
		free(line);
	}
	free(line);
	close(pipedata->fd_input);
}

/* getline will read from the terminal one char at a time and create a string
to be returned to the create_tmp function. Pay extra attention to aux: it is only
used to avoid memory leaks. */
char	*get_one_line(int fd)
{
	char	c;
	char	*str;
	char	*temp;
	char	*aux;

	str = malloc(1 * sizeof(char));
	str[0] = 0;
	while (read(fd, &c, 1) > 0)
	{
		aux = str;
		temp = malloc(2 * sizeof(char));
		temp[0] = c;
		temp[1] = 0;
		str = ft_strjoin(aux, temp);
		free(temp);
		free(aux);
		if (c == '\n')
			break ;
	}
	return (str);
}

/* This function checks for the existence of the here_doc command. If found,
heredoc flag is set to true, limit keyword is registered, and also the number of
commands and the first command are registered. Then, a temporal file is created
to store the inpur from the terminal. */
void	check_for_heredoc(int argc, char **argv, t_pipedata *pipedata)
{
	if (!ft_strncmp(argv[1], "here_doc", 8)
		&& argc >= 5 && check_file(argv[argc - 1], 'W'))
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
