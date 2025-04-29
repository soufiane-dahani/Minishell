/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:26:37 by sodahani          #+#    #+#             */
/*   Updated: 2025/04/27 19:03:02 by yaait-am         ###   ########.fr       */
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
	setup_execution_signals();
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
