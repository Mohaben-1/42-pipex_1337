/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohaben- <mohaben-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 12:24:31 by mohaben-          #+#    #+#             */
/*   Updated: 2025/02/14 19:06:08 by mohaben-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_get_path(char **envp)
{
	char	*full_path;
	int		i;

	i = 0;
	full_path = NULL;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
		{
			full_path = envp[i] + 5;
			break ;
		}
		i++;
	}
	if (full_path == NULL)
		p_error("pipex: Env not found", 127);
	return (ft_strdup(full_path));
}

void	p_error_cmd(char **cmd, char **paths, int exit_status)
{
	write(2, "pipex: ", 7);
	if (cmd[0])
		write(2, cmd[0], ft_strlen(cmd[0]));
	else
		write(2, " ", 1);
	write(2, ": command not found\n", 20);
	free_split(cmd);
	free_split(paths);
	exit(exit_status);
}

void	ft_exec_cmd(char *av, char **envp)
{
	char	**cmd;
	char	**paths;
	char	*full_path;
	char	*the_cmd_path;
	int		i;

	cmd = ft_split(av, ' ');
	if (cmd[0] && !access(cmd[0], X_OK))
		execve(cmd[0], cmd, envp);
	full_path = ft_get_path(envp);
	paths = ft_split(full_path, ':');
	free(full_path);
	i = -1;
	while (paths[++i])
	{
		full_path = ft_strjoin(paths[i], "/");
		the_cmd_path = ft_strjoin(full_path, cmd[0]);
		free(full_path);
		if (the_cmd_path && !access(the_cmd_path, X_OK))
			execve(the_cmd_path, cmd, envp);
		free(the_cmd_path);
	}
	p_error_cmd(cmd, paths, 127);
}
