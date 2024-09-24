/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 10:22:42 by igchurru          #+#    #+#             */
/*   Updated: 2024/09/24 12:08:17 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>

typedef struct s_pipedata
{
	int		fd_input;
	int		fd_output;
	int		pipedes[2];
	bool	valid_path;
	char	**env_vars;	
}	t_pipedata;

//	PIPEX.C
int		main(int argc, char **argv, char **env);
void	pipex(t_pipedata *pipedata, char **argv, char **env);
void	act_first_child(t_pipedata *pipedata, char **argv, char **env);
void	act_second_child(t_pipedata *pipedata, char **argv, char **env);
void	act_execve(char *argv, t_pipedata *pipedata, char **env);

//	PIPEX_UTILS.C
void	error_free_exit(char *str, t_pipedata *pipedata);
void	free_matrix(char **to_free);
void	get_path(t_pipedata *pipedata, char **env);
void	checkfiles(char **argv);
void	set_to_zero(t_pipedata *pipedata);

//	FT_SPLIT.C
char	**ft_split(char const *s, char c);

//	GENERAL_UTILS.C
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);

#endif