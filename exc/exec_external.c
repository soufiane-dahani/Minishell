/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:26:37 by sodahani          #+#    #+#             */
/*   Updated: 2025/05/07 15:17:18 by sodahani         ###   ########.fr       */
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

	if (!cmd || !cmd[0])
		return ;
	if (ft_strchr(cmd[0], '/'))
	{
		execute_with_path(cmd, envp);
		return ;
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

static int	handle_parent_process(t_ast *node, pid_t pid)
{
	int		status;
	char	*str;
	int		result;

	str = ft_strjoin("/usr/bin/", node->cmd[0]);
	result = handle_root_errors(node->cmd[0], str, pid);
	if (result)
		return (result);
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	if (WTERMSIG(status) == SIGQUIT)
		write(2, "Quit (core dumped)\n", 19);
	else if (WTERMSIG(status) == SIGINT)
		write(1, "\n", 1);
	return (exit_status(status));
}

int	exec_external(t_ast *node, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (perror("fork"), 1);
	if (pid == 0)
	{
		reset_signals();
		child_process2(node, envp);
		ft_malloc(0, FT_CLEAR);
		exit(1);
	}
	return (handle_parent_process(node, pid));
}
