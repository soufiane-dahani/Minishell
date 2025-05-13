/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:26:37 by sodahani          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/05/12 16:55:16 by yaait-am         ###   ########.fr       */
=======
/*   Updated: 2025/04/29 15:32:43 by yaait-am         ###   ########.fr       */
>>>>>>> dahani
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

<<<<<<< HEAD
void	close_fd(int fd)
{
	if (fd >= 3)
		close(fd);
}

int	get_in_out_file(t_token *redir, int *in_file, int *out_file)
{
	int	fd;

	redir = handle_wildcard(redir);
	while (redir)
	{
		redir->next->value = exp_for_herdoc(redir->next->value);
		if (!redir->next->value[0] || has_space(redir->next->value))
			return (printf("ambiguous redirect\n"), 1);
		redir->next->value = skip_quote(redir->next->value);
		fd = open_file(redir->next->value, redir->type);
		if (fd == -1)
			return (perror(redir->next->value), 1);
		if (redir->type == TYP_REDIN)
		{
			close_fd(*in_file);
			*in_file = fd;
		}
		else
		{
			close_fd(*out_file);
			*out_file = fd;
		}
		redir = redir->next->next;
	}
	return (0);
}

int	get_redirections(t_ast *cmd, int *in_file, int *out_file)
{
	t_token	*redir;

	*in_file = -1;
	*out_file = -1;
	if (!cmd->redir)
		return (0);
	redir = cmd->redir;
	if (get_in_out_file(redir, in_file, out_file))
		return (1);
	if (*in_file != -1 && dup2(*in_file, STDIN_FILENO) == -1)
	{
		perror("dup2");
		ft_malloc(0, FT_CLEAR);
		exit(1);
	}
	if (*out_file != -1 && dup2(*out_file, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		ft_malloc(0, FT_CLEAR);
		exit(1);
	}
	return (0);
}

static void	child_process(t_ast *node, char ***envp, t_export_store *store)
{
	int	in_fd;
	int	out_fd;
	int	exit_status;

	in_fd = -1;
	out_fd = -1;
	reset_signals();
	if (get_redirections(node, &in_fd, &out_fd))
	{
		ft_malloc(0, FT_CLEAR);
		exit(1);
	}
	exit_status = 0;
	if (node->cmd && is_builtin(node->cmd))
		exit_status = exec_builtin(node, envp, store);
	else if (node->cmd && node->cmd[0])
		exit_status = exec_external(node, *envp);
	close_fd(in_fd);
	close_fd(out_fd);
	ft_malloc(0, FT_CLEAR);
	exit(exit_status);
}

int	apply_redirections(t_ast *node, char ***envp, t_export_store *store)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (perror("fork"), -1);
	if (pid == 0)
		child_process(node, envp, store);
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}
=======

static void handle_child_process(t_ast *node, char ***envp, t_export_store *store)
{
	int out_fd;

	out_fd = open_file(node->r->cmd[0], 1);
	if (out_fd == -1)
	{
		perror("open");
		ft_malloc(0, FT_CLEAR);
		exit(1);
	}
	dup2(out_fd, STDOUT_FILENO);
	close(out_fd);
	if (node->l->type == TYP_REDOUT || node->l->type == TYP_REDAPP)
	{
		int left_out_fd = open_file(node->l->r->cmd[0], 1);
		if (left_out_fd == -1)
		{
			perror("open");
			ft_malloc(0, FT_CLEAR);
			exit(1);
		}
		close(left_out_fd);
		t_ast *current = node->l;
		while (current->type == TYP_REDOUT || current->type == TYP_REDAPP)
		{
			if (current->type == TYP_REDOUT || current->type == TYP_REDAPP)
			{
				int intermediate_fd = open_file(current->r->cmd[0], 1);
				if (intermediate_fd != -1)
					close(intermediate_fd);
			}
			current = current->l;
		}
		execute_ast(current, envp, store);
	}
	else
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

>>>>>>> dahani
