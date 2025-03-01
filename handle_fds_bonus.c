/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fds_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohaben- <mohaben-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 12:20:59 by mohaben-          #+#    #+#             */
/*   Updated: 2025/02/14 20:36:41 by mohaben-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	p_error_file(char *file, int exit_status)
{
	write(2, "pipex: ", 7);
	p_error(file, exit_status);
}

void	ft_here_doc(t_data *data)
{
	char	*line;
	char	*limiter;

	dup2(data->pipe_fd[0][1], 1);
	limiter = ft_strjoin(data->av[2], "\n");
	if (!limiter)
		p_error("pipex: Memory allocation failed", 1);
	while (1)
	{
		write(2, "pipex heredoc> ", 15);
		line = get_next_line(0);
		if (!line)
			break ;
		if (!ft_strncmp(line, limiter, ft_strlen(limiter)))
		{
			free(line);
			break ;
		}
		write(1, line, ft_strlen(line));
		free(line);
	}
	free(limiter);
	ft_close_all_pipe_fd(data);
	free_pipes(data);
	exit(0);
}

void	ft_in_proc(t_data *data)
{
	int		fd_in;

	if (!ft_strncmp(data->av[1], "here_doc", 9))
	{
		ft_here_doc(data);
		ft_exec_cmd(data->av[3], data->envp);
	}
	else
	{
		fd_in = open(data->av[1], O_RDONLY);
		if (fd_in == -1)
		{
			ft_close_all_pipe_fd(data);
			free_pipes(data);
			p_error_file(data->av[1], 0);
		}
		dup2(fd_in, 0);
		dup2(data->pipe_fd[0][1], 1);
		close(fd_in);
		ft_close_all_pipe_fd(data);
		free_pipes(data);
		ft_exec_cmd(data->av[2], data->envp);
	}
}

void	ft_mid_proc(t_data *data, int i)
{
	if (i - 2 < 0 || i - 1 >= data->ac - 4)
	{
		ft_close_all_pipe_fd(data);
		free_pipes(data);
		exit(1);
	}
	if (!data->pipe_fd || !data->pipe_fd[i - 2] || !data->pipe_fd[i - 1])
		p_error("pipex: Pipe array corruption", 1);
	dup2(data->pipe_fd[i - 2][0], 0);
	dup2(data->pipe_fd[i - 1][1], 1);
	ft_close_all_pipe_fd(data);
	free_pipes(data);
	ft_exec_cmd(data->av[i + 1], data->envp);
}

void	ft_out_proc(t_data *data)
{
	int		fd_out;
	int		fd_pipe;
	char	*outfile;

	outfile = data->av[data->ac - 1];
	if (!ft_strncmp(data->av[1], "here_doc", 9))
		fd_out = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd_out = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out == -1)
	{
		ft_close_all_pipe_fd(data);
		free_pipes(data);
		p_error_file(outfile, 1);
	}
	fd_pipe = data->pipe_fd[data->ac - 5][0];
	dup2(fd_pipe, 0);
	dup2(fd_out, 1);
	close(fd_out);
	ft_close_all_pipe_fd(data);
	free_pipes(data);
	ft_exec_cmd(data->av[data->ac - 2], data->envp);
}
