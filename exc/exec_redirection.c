/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:26:37 by sodahani          #+#    #+#             */
/*   Updated: 2025/04/19 20:58:42 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	open_file(char *filename, int mode)
{
	int	fd;

	if (mode == 0) // >> append
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (mode == 1) // > truncate
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (mode == 2) // < read
		fd = open(filename, O_RDONLY);
	else
		return (-1);
	return (fd);
}


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



int	exec_redirection(t_ast *node, char ***envp)
{
	if (!node || !(node->type == TYP_REDOUT || node->type == TYP_REDAPP ||
		node->type == TYP_REDIN || node->type == TYP_REDHERE))
		return (1);

	if (node->type == TYP_REDOUT)
		return typ_redout_fun(node, envp);

	// You can later add:
	// if (node->type == TYP_REDAPP) ...
	// if (node->type == TYP_REDIN) ...
	// if (node->type == TYP_REDHERE) ...
	
	return (1);
}

