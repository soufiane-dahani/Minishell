/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:26:37 by sodahani          #+#    #+#             */
/*   Updated: 2025/05/10 13:31:46 by yaait-am         ###   ########.fr       */
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

void	print_env_line(char *var)
{
	char	*equal;
	int		key_len;

	equal = ft_strchr(var, '=');
	if (equal)
	{
		key_len = equal - var;
		write(1, "declare -x ", 11);
		write(1, var, key_len);
		write(1, "=\"", 2);
		ft_putstr_fd(equal + 1, 1);
		write(1, "\"\n", 2);
	}
	else
	{
		write(1, "declare -x ", 11);
		ft_putstr_fd(var, 1);
		write(1, "\n", 1);
	}
}
