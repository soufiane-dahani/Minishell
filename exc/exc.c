/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:26:37 by sodahani          #+#    #+#             */
/*   Updated: 2025/05/05 07:57:57 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(char **cmd)
{
	if (!cmd || !cmd[0])
		return (0);
	return (!ft_strcmp(cmd[0], "cd") || !ft_strcmp(cmd[0], "export")
		|| !ft_strcmp(cmd[0], "unset") || !ft_strcmp(cmd[0], "exit")
		|| !ft_strcmp(cmd[0], "env") || !ft_strcmp(cmd[0], "echo")
		|| !ft_strcmp(cmd[0], "pwd"));
}

int	exec_builtin(t_ast *node, char ***envp_ptr, t_export_store *store)
{
	if (!node || !node->cmd || !node->cmd[0])
		return (1);
	if (!ft_strcmp(node->cmd[0], "cd"))
		return (my_cd(node->cmd, envp_ptr));
	if (!ft_strcmp(node->cmd[0], "pwd"))
		return (my_pwd());
	if (!ft_strcmp(node->cmd[0], "echo"))
		return (my_echo(node->cmd));
	if (!ft_strcmp(node->cmd[0], "env"))
		return (my_env(node->cmd, *envp_ptr));
	if (!ft_strcmp(node->cmd[0], "export"))
		return (my_export(node->cmd, envp_ptr, store));
	if (!ft_strcmp(node->cmd[0], "unset"))
		return (my_unset(node->cmd, envp_ptr));
	if (!ft_strcmp(node->cmd[0], "exit"))
		return (my_exit(node->cmd));
	return (1);
}

static int	execute_ast_by_type(t_ast *node, char ***envp,
		t_export_store *store)
{
	if (node->type == TYP_PIPE)
		return (exec_pipe(node, envp, store));
	else if (node->type == TYP_AND)
		return (exec_and(node, envp, store));
	else if (node->type == TYP_OR)
		return (exec_or(node, envp, store));
	else if (node->type == TYP_LPAR)
		return (exec_subshell(node, envp, store));
	return (1);
}

int	execute_ast(t_ast *node, char ***envp, t_export_store *store)
{
	if (!node)
		return (1);
	node->cmd = handle_exp_for_camond(node->cmd);
	if (!is_token_sep(node->type) && node->type != TYP_LPAR)
	{
		if (node->redir)
			return (apply_redirections(node, envp, store));
		else if (is_builtin(node->cmd))
			return (exec_builtin(node, envp, store));
		else
			return (exec_external(node, *envp));
	}
	return (execute_ast_by_type(node, envp, store));
}
