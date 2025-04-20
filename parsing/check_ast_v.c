/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ast_v.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 15:21:32 by yaait-am          #+#    #+#             */
/*   Updated: 2025/04/20 10:43:19 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_builtins(char *cmd)
{
	return (!ft_strncmp(cmd, "echo", 5)
		|| !ft_strncmp(cmd, "cd", 3)
		|| !ft_strncmp(cmd, "pwd", 4)
		|| !ft_strncmp(cmd, "export", 7)
		|| !ft_strncmp(cmd, "unset", 6)
		|| !ft_strncmp(cmd, "env", 4)
		|| !ft_strncmp(cmd, "exit", 5));
}

static int	comond_not_found(char *cmd)
{
	char	*path;
	char	**paths;
	char	*test;
	char	*tmp;
	int		i;

	if (!cmd || !*cmd)
		return (1);
	path = getenv("PATH");
	if (access(cmd, X_OK) == 0 || is_builtins(cmd))
		return (0);
	paths = ft_split(path, ':');
	if (!paths)
		return (1);
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		test = ft_strjoin(tmp, cmd);
		if (access(test, X_OK) == 0)
			return (0);
		i++;
	}
	return (1);
}

static int	check_ast_is_valid_rec(t_ast *node)
{
	if (!node)
		return (1);
	if ((node->type == TYP_AND || node->type == TYP_OR
			|| node->type == TYP_PIPE) && (!node->l || !node->r))
	{
		printf("syntax error near unexpected token `%s'\n",
			node->cmd[0]);
		return (0);
	}
	if (!check_ast_is_valid_rec(node->l))
		return (0);
	if (!check_ast_is_valid_rec(node->r))
		return (0);
	if (!node->l && !node->r && comond_not_found(node->cmd[0]))
	{
		printf("command not found: %s\n", node->cmd[0]);
		return (0);
	}
	return (1);
}

int	check_ast_is_valid(void)
{
	return (check_ast_is_valid_rec(g_ast));
}
