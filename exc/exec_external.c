/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:26:37 by sodahani          #+#    #+#             */
/*   Updated: 2025/04/28 20:15:44 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		if (access(path, F_OK) == 0)
			return (path);
		i++;
	}
	return (NULL);
}

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;

	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PATH=", 5) == 0)
		i++;
	if (!envp[i])
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	path = check_command_in_paths(cmd, paths);
	i = -1;
	return (path);
}

void	execute(char **cmd, char **envp)
{
	char	*path;

	if (ft_strchr(cmd[0], '/'))
	{
		if (access(cmd[0], F_OK | X_OK) == -1)
		{
			ft_malloc(0, FT_CLEAR);
			perror("command not found");
		}
		else
			if (execve(cmd[0], cmd, envp) == -1)
				perror("error ");
		ft_malloc(0, FT_CLEAR);
		exit(127);
	}
	path = find_path(cmd[0], envp);
	if (!path)
	{
		write(2, "command not found\n", 19);
		ft_malloc(0, FT_CLEAR);
		exit(127);
	}
	execve(path, cmd, envp);
	perror("execve failed");
	exit(1);
}

int	is_root(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] == '/')
		i++;
	if (!s[i])
		return (1);
	return (0);
}

int	exec_external(t_ast *node, char **envp)
{
	pid_t	pid;
	int		status;
	char	*str;

	status = 0;
	pid = fork();
	reset_signals();
	setup_execution_signals();
	if (pid == -1)
		return (perror("fork"), 1);
	if (pid == 0)
	{
		execute(node->cmd, envp);
		ft_malloc(0, FT_CLEAR);
		exit(1);
	}
	else
	{
		str = ft_strjoin("/usr/bin/", node->cmd[0]);
		if (access(str, F_OK | X_OK) == -1 && access(node->cmd[0], F_OK | X_OK) == -1)
			return (waitpid(pid, &status, 0), 127);
		if (is_root(node->cmd[0]))
			return (waitpid(pid, &status, 0), 126);
		g_ast->exit_status = exit_status(status);
		waitpid(pid, &status, 0);
		return (g_ast->exit_status);
	}
}
