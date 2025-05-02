/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:26:37 by sodahani          #+#    #+#             */
/*   Updated: 2025/05/02 16:53:48 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_subshell(t_ast *node, char ***envp, t_export_store *store)
{
	pid_t	pid;
	int		status;
	int		i;

	pid = fork();
	reset_signals();
	if (pid == -1)
		return (perror("fork"), 1);
	if (pid == 0)
	{
		i = execute_ast(node->r, envp, store);
		ft_malloc(0, FT_CLEAR);
		exit(i);
	}
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}
