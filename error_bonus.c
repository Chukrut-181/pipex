/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 09:54:40 by igchurru          #+#    #+#             */
/*   Updated: 2024/09/27 10:38:45 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	error_exit(char *str)
{
	ft_putstr_fd(str, 2);
	exit (-1);
}

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

void	free_pipedes(t_pipedata *pipedata)
{
	int	i;

	i = 0;
	while (i < pipedata->n_of_commands - 1)
	{
		free(pipedata->pipedes[i]);
		i++;
	}
	free(pipedata->pipedes);
}
