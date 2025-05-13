/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:26:37 by sodahani          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/05/12 12:41:09 by yaait-am         ###   ########.fr       */
=======
/*   Updated: 2025/04/27 19:03:02 by yaait-am         ###   ########.fr       */
>>>>>>> dahani
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
<<<<<<< HEAD
=======
	setup_execution_signals();
>>>>>>> dahani
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
<<<<<<< HEAD

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
=======
>>>>>>> dahani
