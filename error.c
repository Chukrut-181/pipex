/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 10:06:52 by igchurru          #+#    #+#             */
/*   Updated: 2024/09/25 10:08:34 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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