/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:26:37 by sodahani          #+#    #+#             */
/*   Updated: 2025/04/17 19:37:54 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

void	free_split(char **arr)
{
	int i = 0;
	while (arr && arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char	*check_command_in_paths(char *cmd, char **paths)
{
	char	*path;
	char	*part_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK | X_OK) == 0)
		{
			free_split(paths);
			return (path);
		}
		free(path);
		i++;
	}
	free_split(paths);
	return (NULL);
}

char	*find_path(char *cmd, char **envp)
{
	int		i = 0;
	char	**paths;
	char	*path;

	while (envp[i] && ft_strnstr(envp[i], "PATH=", 5) == 0)
		i++;
	if (!envp[i])
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	if (!paths)
		return (NULL);
	path = check_command_in_paths(cmd, paths);
	return (path);
}

int	execute_simple_command(char **cmd, char **envp)
{
	char	*path;
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork failed");
		return (1);
	}
	if (pid == 0)
	{
		if (ft_strchr(cmd[0], '/'))
		{
			if (access(cmd[0], F_OK | X_OK) == -1)
			{
				perror("error");
				exit(127);
			}
			execve(cmd[0], cmd, envp);
		}
		path = find_path(cmd[0], envp);
		if (!path)
		{
			write(2, "error: command not found\n", 25);
			exit(127);
		}
		execve(path, cmd, envp);
		perror("execve failed");
		free(path);
		exit(126);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
		return WEXITSTATUS(status);
		else
		return 1;
	}
}

