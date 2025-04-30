/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:26:37 by sodahani          #+#    #+#             */
/*   Updated: 2025/04/30 13:39:47 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		else if (execve(cmd[0], cmd, envp) == -1)
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
	ft_malloc(0, FT_CLEAR);
	exit(1);
}

static void	child_process(t_ast *node, char **envp)
{
	execute(node->cmd, envp);
	ft_malloc(0, FT_CLEAR);
	exit(1);
}

static int	handle_root_errors(char *cmd, char *str, pid_t pid)
{
	int	status;
	int	root_status;

	root_status = is_root(cmd, str);
	if (root_status == 127 || root_status == 126)
	{
		waitpid(pid, &status, 0);
		signal(SIGINT, handler_interactive);
		return (root_status);
	}
	return (0);
}

int	exec_external(t_ast *node, char **envp)
{
	pid_t	pid;
	int		status;
	char	*str;
	int		result;

	status = 0;
	pid = fork();
	reset_signals();
	if (pid == -1)
		return (perror("fork"), 1);
	if (pid == 0)
		child_process(node, envp);
	signal(SIGINT, SIG_IGN);
	str = ft_strjoin("/usr/bin/", node->cmd[0]);
	result = handle_root_errors(node->cmd[0], str, pid);
	if (result)
		return (result);
	waitpid(pid, &status, 0);
	g_ast->exit_status = exit_status(status);
	signal(SIGINT, handler_interactive);
	return (g_ast->exit_status);
}
