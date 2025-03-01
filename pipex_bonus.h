/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohaben- <mohaben-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 13:31:02 by mohaben-          #+#    #+#             */
/*   Updated: 2025/02/14 17:19:34 by mohaben-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>

typedef struct s_data
{
	int		**pipe_fd;
	char	**av;
	char	**envp;
	int		status;
	int		ac;
}	t_data;

size_t	ft_strlen(const char *s);
int		ft_strchr(const char *str, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
void	free_split(char **s);
void	p_error(char *err, int exit_status);
char	*get_next_line(int fd);
void	ft_in_proc(t_data *data);
void	ft_mid_proc(t_data *data, int i);
void	ft_out_proc(t_data *data);
char	*ft_get_path(char **envp);
void	ft_exec_cmd(char *av, char **envp);
void	ft_close_all_pipe_fd(t_data *data);
void	ft_here_doc(t_data *data);
void	free_pipes(t_data *data);

#endif