/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:26:37 by sodahani          #+#    #+#             */
/*   Updated: 2025/04/24 14:50:56 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	handle_left_pipe(t_ast *node, char ***envp, int fd[2], t_export_store *store)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (perror("fork"), 1);
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		execute_ast(node->l, envp, store);
		exit(1);
	}
	return (pid);
}

static int	handle_right_pipe(t_ast *node, char ***envp, int fd[2], t_export_store *store)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (perror("fork"), 1);
	if (pid == 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		execute_ast(node->r, envp, store);
		exit(1);
	}
	return (pid);
}

int	exec_pipe(t_ast *node, char ***envp, t_export_store *store)
{
	int		fd[2];
	int		status;
	pid_t	pid1;
	pid_t	pid2;

	if (!node || node->type != TYP_PIPE)
		return (1);
	if (pipe(fd) == -1)
		return (perror("pipe"), 1);
	pid1 = handle_left_pipe(node, envp, fd, store);
	pid2 = handle_right_pipe(node, envp, fd, store);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
	return (WEXITSTATUS(status));
}
