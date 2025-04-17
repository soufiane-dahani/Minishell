/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:26:37 by sodahani          #+#    #+#             */
/*   Updated: 2025/04/17 11:34:35 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

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
	int	fd;

	if (!node || !node->cmd || !node->cmd[0])
		return ;

	if (node->type == TYP_REDIN)
		fd = open(node->cmd[1], O_RDONLY);
	else if (node->type == TYP_REDOUT)
		fd = open(node->cmd[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (node->type == TYP_REDAPP)
		fd = open(node->cmd[1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
	{
		*exit_status = 1;
		return ;
	}

	if (fd < 0)
	{
		perror("minishell: redirection");
		*exit_status = 1;
		return ;
	}

	if (node->type == TYP_REDIN)
		dup2(fd, STDIN_FILENO);
	else
		dup2(fd, STDOUT_FILENO);

	close(fd);

	if (node->l)
		execute_ast(node->l, envp_ptr, exit_status);
	else
		*exit_status = 0;
}

void	execute_ast(t_ast *node, char ***envp_ptr, int *exit_status)
{
	if (!node)
	{
		*exit_status = 1;
		return ;
	}

	if (node->type == TYP_WORD)
		execute_simple(node, envp_ptr, exit_status);
	else if (node->type == TYP_PIPE)
		*exit_status = execute_pipe(node, *envp_ptr);
	else if (node->type == TYP_REDIN || node->type == TYP_REDOUT || node->type == TYP_REDAPP)
		handle_redir(node, envp_ptr, exit_status);
	else if (node->type == TYP_AND || node->type == TYP_OR)
	{
		execute_ast(node->l, envp_ptr, exit_status);
		if ((node->type == TYP_AND && *exit_status == 0) ||
			(node->type == TYP_OR && *exit_status != 0))
			execute_ast(node->r, envp_ptr, exit_status);
	}
}

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    (void)envp;
}
