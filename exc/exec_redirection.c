/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:26:37 by sodahani          #+#    #+#             */
/*   Updated: 2025/04/28 14:37:53 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	handle_child_process(t_ast *node, char ***envp,
		t_export_store *store)
{
	int	out_fd;

	out_fd = open_file(node->r->cmd[0], 1);
	if (out_fd == -1)
	{
		perror("open");
		ft_malloc(0, FT_CLEAR);
		exit(1);
	}
	dup2(out_fd, STDOUT_FILENO);
	close(out_fd);
	execute_ast(node->l, envp, store);
	ft_malloc(0, FT_CLEAR);
	exit(1);
}

int	typ_redout_fun(t_ast *node, char ***envp, t_export_store *store)
{
	pid_t	pid;
	int		status;
	int		i;

	pid = fork();
	reset_signals();
	setup_execution_signals();
	if (pid == -1)
		return (perror("fork"), 1);
	if (pid == 0)
		handle_child_process(node, envp, store);
	waitpid(pid, &status, 0);
	i = WEXITSTATUS(status);
	if (i == 1)
		ft_putstr_fd("echo: write error\n", 2);
	return (i);
}

int	typ_redin_fun(t_ast *node, char ***envp, t_export_store *store)
{
	pid_t	pid;
	int		status;
	int		in_fd;

	pid = fork();
	reset_signals();
	setup_execution_signals();
	if (pid == -1)
		return (perror("fork"), 1);
	if (pid == 0)
	{
		in_fd = open_file(node->r->cmd[0], 2);
		if (in_fd == -1)
		{
			perror("open");
			ft_malloc(0, FT_CLEAR);
			exit(1);
		}
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
		execute_ast(node->l, envp, store);
		ft_malloc(0, FT_CLEAR);
		exit(1);
	}
	return (waitpid(pid, &status, 0), WEXITSTATUS(status));
}

int	typ_redapp_fun(t_ast *node, char ***envp, t_export_store *store)
{
	pid_t	pid;
	int		status;
	int		out_fd;

	pid = fork();
	reset_signals();
	setup_execution_signals();
	if (pid == -1)
		return (perror("fork"), 1);
	if (pid == 0)
	{
		out_fd = open_file(node->r->cmd[0], 0);
		if (out_fd == -1)
		{
			perror("open");
			ft_malloc(0, FT_CLEAR);
			exit(1);
		}
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);
		execute_ast(node->l, envp, store);
		ft_malloc(0, FT_CLEAR);
		exit(1);
	}
	return (waitpid(pid, &status, 0), WEXITSTATUS(status));
}

int	exec_redirection(t_ast *node, char ***envp, t_export_store *store)
{
	if (!node || !(node->type == TYP_REDOUT || node->type == TYP_REDAPP
			|| node->type == TYP_REDIN || node->type == TYP_REDHERE))
		return (1);
	if (node->type == TYP_REDOUT)
		return (typ_redout_fun(node, envp, store));
	else if (node->type == TYP_REDIN)
		return (typ_redin_fun(node, envp, store));
	else if (node->type == TYP_REDAPP)
		return (typ_redapp_fun(node, envp, store));
	else if (node->type == TYP_REDHERE)
		return (typ_redhere_fun(node, envp, store));
	return (1);
}
