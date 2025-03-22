/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_ast.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:42:19 by yaait-am          #+#    #+#             */
/*   Updated: 2025/03/22 15:35:58 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*build_the_tree(t_token *tk)
{
	t_token	*op;
	t_token	*prev;

	prev = tk;
	op = NULL;
	while (prev)
	{
		if (prev->type == TYP_AND || prev->type == TYP_PIPE || prev->type == TYP_OR)
			op = prev;
		prev = prev->next;
	}
	if (op)
		printf("the head of the ast : %s\n", op->value);
	else
	{
		printf("No operator found. Treating the whole input as a single command.\n");
	}
	return (g_ast);
}

t_ast *new_ast_node(t_type type, char *cmd, char *per, int exp)
{
	t_ast *node;

	node = ft_malloc(sizeof(t_ast), FT_ALLOC);
	if (!node)
		return NULL;
	node->type = type;
	node->cmd[0] = cmd;
	node->cmd[1] = per;
	node->exp = exp;
	node->l = NULL;
	node->r = NULL;
	return node;
}
