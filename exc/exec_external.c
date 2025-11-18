/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yassir <yassir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:26:37 by sodahani          #+#    #+#             */
/*   Updated: 2025/11/18 16:51:44 by yassir           ###   ########.fr       */
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
	if (cmd[0][0] == '\0' && !cmd[1])
		return ;
	if (cmd[0][0] == '\0' && cmd[1][0])
		cmd++;
	if (ft_strchr(cmd[0], '/'))
	{
		execute_with_path(cmd, envp);
		return ;
	}
	path = find_path(cmd[0], envp);
	if (!path)
	{
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		ft_malloc(0, FT_CLEAR);
		exit(127);
	}
	execve(path, cmd, envp);
	perror("execve failed");
	ft_malloc(0, FT_CLEAR);
	exit(1);
}

static int	handle_parent_process(t_ast *node, pid_t pid)
{
	int		status;

	if (node->cmd[0][0] == '\0' && !node->cmd[1])
		return (0);
	if (node->cmd[0][0] == '\0' && node->cmd[1][0])
		node->cmd++;
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
