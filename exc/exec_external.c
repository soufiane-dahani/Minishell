/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:26:37 by sodahani          #+#    #+#             */
/*   Updated: 2025/05/11 15:20:42 by yaait-am         ###   ########.fr       */
=======
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:26:37 by sodahani          #+#    #+#             */
/*   Updated: 2025/04/28 21:40:22 by sodahani         ###   ########.fr       */
>>>>>>> dahani
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

<<<<<<< HEAD
=======
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

>>>>>>> dahani
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

<<<<<<< HEAD
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
=======
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
>>>>>>> dahani
	}
	path = find_path(cmd[0], envp);
	if (!path)
	{
<<<<<<< HEAD
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd(": command not found\n", 2);
=======
		write(2, "command not found\n", 19);
>>>>>>> dahani
		ft_malloc(0, FT_CLEAR);
		exit(127);
	}
	execve(path, cmd, envp);
	perror("execve failed");
<<<<<<< HEAD
	ft_malloc(0, FT_CLEAR);
	exit(1);
}

static int	handle_parent_process(t_ast *node, pid_t pid)
{
	int		status;
	char	*str;

	if (node->cmd[0][0] == '\0' && !node->cmd[1])
		return (0);
	if (node->cmd[0][0] == '\0' && node->cmd[1][0])
		node->cmd++;
	str = ft_strjoin("/usr/bin/", node->cmd[0]);
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	if (WTERMSIG(status) == SIGQUIT)
		write(2, "Quit (core dumped)\n", 19);
	else if (WTERMSIG(status) == SIGINT)
		write(1, "\n", 1);
	return (exit_status(status));
=======
	exit(1);
}

int	is_root(char *s, char *str)
{
	int	i;

	i = 0;
	if (access(str, F_OK | X_OK) == -1 && access(s,
			F_OK | X_OK) == -1)
		return (127);
	while (s[i] && s[i] == '/')
		i++;
	if (!s[i])
		return (126);
	return (0);
>>>>>>> dahani
}

int	exec_external(t_ast *node, char **envp)
{
	pid_t	pid;
<<<<<<< HEAD

	pid = fork();
=======
	int		status;
	char	*str;

	(1) && (status = 0), (pid = fork());
	reset_signals();
	setup_execution_signals();
>>>>>>> dahani
	if (pid == -1)
		return (perror("fork"), 1);
	if (pid == 0)
	{
<<<<<<< HEAD
		reset_signals();
		child_process2(node, envp);
		ft_malloc(0, FT_CLEAR);
		exit(1);
	}
	return (handle_parent_process(node, pid));
=======
		execute(node->cmd, envp);
		ft_malloc(0, FT_CLEAR);
		exit(1);
	}
	else
	{
		str = ft_strjoin("/usr/bin/", node->cmd[0]);
		if (is_root(node->cmd[0], str) == 127)
			return (waitpid(pid, &status, 0), 127);
		if (is_root(node->cmd[0], str) == 126)
			return (waitpid(pid, &status, 0), 126);
		g_ast->exit_status = exit_status(status);
		return (waitpid(pid, &status, 0), g_ast->exit_status);
	}
>>>>>>> dahani
}
