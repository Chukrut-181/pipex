/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 10:22:42 by igchurru          #+#    #+#             */
/*   Updated: 2024/09/11 13:37:32 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>

typedef struct s_pipedata
{
	int		fd_input;
	int 	fd_output;
	int		pipedes[2];
	bool	valid_path;
	char	**env_vars;	
} t_pipedata;

//	PIPEX.C
int		main(int argc, char **argv, char **env);
void	pipex(t_pipedata *pipedata, char **argv, char **env);
void	act_child(t_pipedata *pipedata, char **argv, char **env);
void	act_parent(t_pipedata *pipedata, char **argv, char **env);

//	PIPEX_UTILS.C
void	checkfiles (int argc, char **argv);
void	set_to_zero(t_pipedata *pipedata);

#endif