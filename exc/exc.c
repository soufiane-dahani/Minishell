/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:26:37 by sodahani          #+#    #+#             */
/*   Updated: 2025/04/17 19:35:16 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

static int	is_builtin(char *cmd)
{
	if (!cmd) return 0;
	return (ft_strncmp(cmd, "cd", 3) == 0
		|| ft_strncmp(cmd, "export", 7) == 0
		|| ft_strncmp(cmd, "unset", 6) == 0
		|| ft_strncmp(cmd, "exit", 5) == 0
		|| ft_strncmp(cmd, "pwd", 4) == 0
		|| ft_strncmp(cmd, "env", 4) == 0);
}

static void	handle_builtin(t_ast *node, char ***envp_ptr, int *exit_status)
{
	if (!node->cmd || !node->cmd[0])
	{
		*exit_status = 1;
		return ;
	}
	if (ft_strncmp(node->cmd[0], "cd", 3) == 0)
		*exit_status = execute_cd(node->cmd[1]);
	else if (ft_strncmp(node->cmd[0], "export", 7) == 0)
	{
		if (!node->cmd[1])
			print_export(*envp_ptr);
		else
			*exit_status = execute_export(envp_ptr, node->cmd);
	}
	else if (ft_strncmp(node->cmd[0], "unset", 6) == 0)
		*exit_status = execute_unset(envp_ptr, node->cmd[1]);
	else if (ft_strncmp(node->cmd[0], "exit", 5) == 0)
		execute_exit();
	else if (ft_strncmp(node->cmd[0], "pwd", 4) == 0)
		*exit_status = execute_pwd();
	else if (ft_strncmp(node->cmd[0], "env", 4) == 0)
		*exit_status = execute_env(*envp_ptr);
	else
		*exit_status = 1;
}

static void	execute_simple(t_ast *node, char ***envp_ptr, int *exit_status)
{
	if (!node->cmd || !node->cmd[0])
	{
		*exit_status = 1;
		return ;
	}

	if (is_builtin(node->cmd[0]))
		handle_builtin(node, envp_ptr, exit_status);
	else
		*exit_status = execute_simple_command(node->cmd, *envp_ptr); // you must implement this
}

static void	handle_redir(t_ast *node, char ***envp_ptr, int *exit_status)
{
	// int	fd;

	// if (!node || !node->cmd || !node->cmd[0])
	// 	return ;

	// if (node->type == TYP_REDIN)
	// 	fd = open(node->cmd[1], O_RDONLY);
	// else if (node->type == TYP_REDOUT)
	// 	fd = open(node->cmd[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	// else if (node->type == TYP_REDAPP)
	// 	fd = open(node->cmd[1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	// else
	// {
	// 	*exit_status = 1;
	// 	return ;
	// }

	// if (fd < 0)
	// {
	// 	perror("minishell: redirection");
	// 	*exit_status = 1;
	// 	return ;
	// }

	// if (node->type == TYP_REDIN)
	// 	dup2(fd, STDIN_FILENO);
	// else
	// 	dup2(fd, STDOUT_FILENO);

	// close(fd);

	// // if (node->l)
	// // 	execute_ast(node->l, envp_ptr, exit_status);

	// *exit_status = 0;
}

void	execute_ast(char ***envp_ptr)
{
	if (!g_ast)
	{
		*g_ast->suc = 1;
		return ;
	}
	if (g_ast->type == TYP_WORD)
		execute_simple(g_ast, envp_ptr, g_ast->suc);
	else if (g_ast->type == TYP_PIPE)
		*g_ast->suc = execute_pipe(g_ast, *envp_ptr);
	else if (g_ast->type == TYP_REDIN || g_ast->type == TYP_REDOUT || g_ast->type == TYP_REDAPP)
		handle_redir(g_ast, envp_ptr, g_ast->suc);
	else if (g_ast->type == TYP_AND || g_ast->type == TYP_OR)
	{
		execute_ast(envp_ptr);
		if ((g_ast->type == TYP_AND && *g_ast->suc == 0) ||
			(g_ast->type == TYP_OR && *g_ast->suc != 0))
			execute_ast(envp_ptr);
	}
}
