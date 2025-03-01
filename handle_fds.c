/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohaben- <mohaben-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 12:20:59 by mohaben-          #+#    #+#             */
/*   Updated: 2025/02/14 20:37:26 by mohaben-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	p_error(char *err, int exit_status)
{
	perror(err);
	exit(exit_status);
}

void	p_error_file(char *file, int exit_status)
{
	write(2, "pipex: ", 7);
	p_error(file, exit_status);
}

void	ft_close_pipe_fd(int *pipe_fd)
{
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}

void	ft_in_proc(t_data *data)
{
	int		fd_in;

	fd_in = open(data->av[1], O_RDONLY);
	if (fd_in == -1)
		p_error_file(data->av[1], 0);
	dup2(fd_in, 0);
	dup2(data->pipe_fd[1], 1);
	close(fd_in);
	ft_close_pipe_fd(data->pipe_fd);
	ft_exec_cmd(data->av[2], data->envp);
}

void	ft_out_proc(t_data *data)
{
	int		fd_out;
	char	*outfile;

	outfile = data->av[data->ac - 1];
	fd_out = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out == -1)
		p_error_file(outfile, 1);
	dup2(data->pipe_fd[0], 0);
	dup2(fd_out, 1);
	close(fd_out);
	ft_close_pipe_fd(data->pipe_fd);
	ft_exec_cmd(data->av[data->ac - 2], data->envp);
}
