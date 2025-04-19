/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ast_v.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 15:21:32 by yaait-am          #+#    #+#             */
/*   Updated: 2025/04/19 15:42:41 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	return (1);
}

int	check_ast_is_valid(void)
{
	return (check_ast_is_valid_rec(g_ast));
}
