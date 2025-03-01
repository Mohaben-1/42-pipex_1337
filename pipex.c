/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohaben- <mohaben-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 13:37:07 by mohaben-          #+#    #+#             */
/*   Updated: 2025/02/08 16:29:58 by mohaben-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_data_init(int ac, char **av, char **envp, t_data *data)
{
	if (ac != 5)
	{
		write(2, "Usage: ./pipex infile cmd1 cmd2 outfile\n", 41);
		exit(1);
	}
	if (pipe(data->pipe_fd) == -1)
		p_error("pipex: Pipe creation failed", 1);
	data->ac = ac;
	data->av = av;
	data->envp = envp;
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;
	pid_t	pid_in;
	pid_t	pid_out;

	ft_data_init(ac, av, envp, &data);
	pid_in = fork();
	if (pid_in < 0)
		p_error("pipex: Fork failed", 1);
	if (pid_in == 0)
		ft_in_proc(&data);
	pid_out = fork();
	if (pid_out < 0)
		p_error("pipex: Fork failed", 1);
	if (pid_out == 0)
		ft_out_proc(&data);
	ft_close_pipe_fd(data.pipe_fd);
	waitpid(pid_out, &(data.status), 0);
	waitpid(pid_in, NULL, 0);
	if (WIFEXITED(data.status))
		return (WEXITSTATUS(data.status));
	return (1);
}
