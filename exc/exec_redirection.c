/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:26:37 by sodahani          #+#    #+#             */
/*   Updated: 2025/04/20 20:20:29 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	typ_redout_fun(t_ast *node, char ***envp)
{
	pid_t	pid;
	int		status;
	int		out_fd;

	pid = fork();
	if (pid == -1)
		return (perror("fork"), 1);

	if (pid == 0)
	{
		out_fd = open_file(node->r->cmd[0], 1);
		if (out_fd == -1)
		{
			perror("open");
			exit(1);
		}
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);

		execute_ast(node->l, envp);
		exit(1);
	}
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}
int	typ_redin_fun(t_ast *node, char ***envp)
{
	pid_t	pid;
	int		status;
	int		in_fd;

	pid = fork();
	if (pid == -1)
		return (perror("fork"), 1);

	if (pid == 0)
	{
		in_fd = open_file(node->r->cmd[0], 2);
		if (in_fd == -1)
		{
			perror("open");
			exit(1);
		}
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);

		execute_ast(node->l, envp);
		exit(1);
	}
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}
int	typ_redapp_fun(t_ast *node, char ***envp)
{
	pid_t	pid;
	int		status;
	int		out_fd;

	pid = fork();
	if (pid == -1)
		return (perror("fork"), 1);

	if (pid == 0)
	{
		out_fd = open_file(node->r->cmd[0], 0);
		if (out_fd == -1)
		{
			perror("open");
			exit(1);
		}
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);

		execute_ast(node->l, envp);
		exit(1);
	}
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}


int	exec_redirection(t_ast *node, char ***envp)
{
	if (!node || !(node->type == TYP_REDOUT || node->type == TYP_REDAPP ||
		node->type == TYP_REDIN || node->type == TYP_REDHERE))
		return (1);

	if (node->type == TYP_REDOUT)
		return typ_redout_fun(node, envp);
	else if (node->type == TYP_REDIN)
		return typ_redin_fun(node, envp);
	else if (node->type == TYP_REDAPP)
		return typ_redapp_fun(node, envp);
	else if (node->type == TYP_REDHERE)
		return typ_redhere_fun(node, envp);	
	return (1);
}

