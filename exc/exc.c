/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:26:37 by sodahani          #+#    #+#             */
/*   Updated: 2025/04/19 13:06:23 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"


int	is_builtin(char **cmd)
{
	if (!cmd || !cmd[0])
		return (0);
	return (!ft_strcmp(cmd[0], "cd")
		|| !ft_strcmp(cmd[0], "export")
		|| !ft_strcmp(cmd[0], "unset")
		|| !ft_strcmp(cmd[0], "exit")
		|| !ft_strcmp(cmd[0], "echo")
		|| !ft_strcmp(cmd[0], "env")
		|| !ft_strcmp(cmd[0], "pwd"));
}

int	exec_builtin(t_ast *node, char ***envp_ptr)
{
	if (!node || !node->cmd || !node->cmd[0])
		return (1);

	if (!ft_strcmp(node->cmd[0], "cd"))
		return (my_cd(node->cmd, envp_ptr));

	if (!ft_strcmp(node->cmd[0], "pwd"))
		return (my_pwd());

	// if (!ft_strcmp(node->cmd[0], "echo"))
	// 	return (my_echo(node->cmd));

	if (!ft_strcmp(node->cmd[0], "env"))
	return (my_env(node->cmd, *envp_ptr));


	if (!ft_strcmp(node->cmd[0], "export"))
		return (my_export(node->cmd, envp_ptr));

	if (!ft_strcmp(node->cmd[0], "unset"))
		return (my_unset(node->cmd, envp_ptr));

	if (!ft_strcmp(node->cmd[0], "exit"))
		return (my_exit(node->cmd));

	return (1);
}


int	execute_ast(t_ast *node, char ***envp)
{
	if (!node)
		return (1);

	if (node->type == TYP_WORD)
	{
		if (is_builtin(node->cmd))
			return exec_builtin(node, envp);
		else
			return exec_external(node, *envp);
	}
	// else if (node->type == TYP_PIPE)
	// 	return exec_pipe(node, envp);
	// else if (node->type == TYP_REDOUT || node->type == TYP_REDAPP ||
	// 		 node->type == TYP_REDIN || node->type == TYP_REDHERE)
	// 	return exec_redirection(node, envp);
	// else if (node->type == TYP_AND)
	// 	return exec_and(node, envp);
	// else if (node->type == TYP_OR)
	// 	return exec_or(node, envp);
	// else if (node->type == TYP_PAR_BLOCK)
	// 	return exec_subshell(node, envp);
	
	return (1);
}


