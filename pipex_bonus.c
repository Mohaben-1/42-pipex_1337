/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohaben- <mohaben-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 13:04:26 by mohaben-          #+#    #+#             */
/*   Updated: 2025/02/14 18:51:29 by mohaben-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_close_all_pipe_fd(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->ac - 4)
	{
		if (data->pipe_fd[i][0] >= 0)
			close(data->pipe_fd[i][0]);
		if (data->pipe_fd[i][1] >= 0)
			close(data->pipe_fd[i][1]);
		i++;
	}
}

void	free_pipes(t_data *data)
{
	int	i;

	if (!data->pipe_fd)
		return ;
	i = 0;
	while (i < data->ac - 4)
	{
		free(data->pipe_fd[i]);
		i++;
	}
	free(data->pipe_fd);
}

static void	ft_data_int(int ac, char **av, char **envp, t_data *data)
{
	int	i;

	if (ac < 5)
	{
		write(2, "Usage: ./pipex infile cmd1 cmd2 ... cmdn outfile\n", 50);
		exit(1);
	}
	data->ac = ac;
	data->av = av;
	data->envp = envp;
	data->pipe_fd = malloc((ac - 4) * sizeof(int *));
	if (!data->pipe_fd)
		p_error("pipex: Memory allocation failed", 1);
	i = 0;
	while (i < ac - 4)
	{
		data->pipe_fd[i] = malloc(2 * sizeof(int));
		if (!data->pipe_fd[i])
			p_error("pipex: Memory allocation failed", 1);
		if (pipe(data->pipe_fd[i]) == -1)
			p_error("pipex: Pipe creation failed", 1);
		i++;
	}
}

int	ft_handle_return(t_data *data, int pid_out)
{
	ft_close_all_pipe_fd(data);
	waitpid(pid_out, &(data->status), 0);
	while (wait(NULL) > 0)
		;
	free_pipes(data);
	if (WIFEXITED(data->status))
		return (WEXITSTATUS(data->status));
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;
	pid_t	pid[3];
	int		i;

	ft_data_int(ac, av, envp, &data);
	pid[0] = fork();
	if (pid[0] < 0)
		p_error("pipex: Fork failed", 1);
	if (pid[0] == 0)
		ft_in_proc(&data);
	i = 1;
	while (++i < ac - 2)
	{
		pid[1] = fork();
		if (pid[1] < 0)
			p_error("pipex: Fork failed", 1);
		if (pid[1] == 0)
			ft_mid_proc(&data, i);
	}
	pid[2] = fork();
	if (pid[2] < 0)
		p_error("pipex: Fork failed", 1);
	if (pid[2] == 0)
		ft_out_proc(&data);
	return (ft_handle_return(&data, pid[2]));
}
