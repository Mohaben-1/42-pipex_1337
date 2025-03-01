/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohaben- <mohaben-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 13:31:02 by mohaben-          #+#    #+#             */
/*   Updated: 2025/02/14 17:19:10 by mohaben-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>

typedef struct s_data
{
	int		pipe_fd[2];
	int		status;
	char	**av;
	char	**envp;
	int		ac;
}	t_data;

size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
int		ft_strchr(const char *str, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
void	free_split(char **s);
void	p_error(char *err, int exit_status);
void	ft_close_pipe_fd(int *pipe_fd);
void	ft_in_proc(t_data *data);
void	ft_out_proc(t_data *data);
char	*ft_get_path(char **envp);
void	ft_exec_cmd(char *av, char **envp);

#endif