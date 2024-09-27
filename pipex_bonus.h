/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 10:22:42 by igchurru          #+#    #+#             */
/*   Updated: 2024/09/27 12:41:11 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <sys/wait.h>

typedef struct s_pipedata
{
	int		fd_input;
	int		fd_output;
	int		**pipedes;
	bool	valid_path;
	bool	heredoc;
	char	*limit;
	int		n_of_commands;
	int		first_command;
	char	**env_vars;
	int		argc_count;
}	t_pipedata;

//	PIPEX_BONUS.C
int		main(int argc, char **argv, char **env);
void	pipex(t_pipedata *pipedata, int argc, char **argv, char **env);
void	act_first_child(t_pipedata *pipedata, char **argv, char **env);
void	act_middle_children(int i, t_pipedata *pipedata,
			char **argv, char **env);
void	act_last_child(int i, t_pipedata *pipedata,
			char **argv, char **env);

//	PIPEX_UTILS_BONUS.C
void	check_for_heredoc(int argc, char **argv, t_pipedata *pipedata);
int		check_file(char *file, char c);
void	create_pipes(t_pipedata *pipedata);
void	close_pipe(t_pipedata *pipedata, int k);
void	act_execve(t_pipedata *pipedata, char *argv, char **env);

//	FT_SPLIT.C
char	**ft_split(char const *s, char c);

//	GENERAL_UTILS_BONUS.C
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	ft_putstr_fd(char *s, int fd);

//	GENERAL_UTILS2_BONUS.C
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_bzero(void *s, size_t n);
void	get_path(t_pipedata *pipedata, char **env);

//	CREATE_TMP_BONUS.C
void	create_tmp(t_pipedata *pipedata);
char	*get_one_line(int fd);

//	ERROR_BONUS.C
void	error_exit(char *str);
void	error_free_exit(char *str, t_pipedata *pipedata);
void	free_matrix(char **to_free);
void	free_pipedes(t_pipedata *pipedata);

#endif