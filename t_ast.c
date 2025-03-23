/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_ast.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:42:19 by yaait-am          #+#    #+#             */
/*   Updated: 2025/03/23 15:57:34 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char **convert_tokens_to_array(t_token *tk)
{
	int count = 0;
	t_token *tmp = tk;
	char **cmd_array;

	while (tmp && tmp->type == TYP_WORD)
	{
		count++;
		tmp = tmp->next;
	}

	cmd_array = ft_malloc(sizeof(char *) * (count + 1), 0);
	if (!cmd_array)
		return NULL;

	for (int i = 0; i < count; i++)
	{
		cmd_array[i] = ft_strdup(tk->value);
		tk = tk->next;
	}
	cmd_array[count] = NULL;
	return cmd_array;
}

static t_token *creat_new_tk(t_token *tk, t_token *op)
{
	t_token *node = NULL;
	t_token *cur = NULL;

	while (tk != op)
	{
		if (!node)
		{
			node = tk;
			cur = node;
		}
		else
		{
			cur->next = tk;
			cur = cur->next;
		}
		tk = tk->next;
	}
	if (cur)
		cur->next = NULL;
	return node;
}

static char	**new_cmd(t_token *op)
{
	t_token	*p;
	char	**cmd = ft_malloc(sizeof(char *), FT_ALLOC);

	p = op;
	if (op->type == TYP_WORD && op->type == TYP_WORD)
	{
		cmd[0] = op->value;
		cmd[1] = op->next->value;
		return (cmd);
	}
	cmd[0] = op->value;
	cmd[1] = NULL;
	return (cmd);
}

t_ast *build_the_tree(t_token *tk)
{
	t_token *prev = NULL;
	t_token *op = NULL;
	t_token *left_tokens = NULL;
	t_token *right_tokens = NULL;
	t_ast *node = NULL;
	while (tk)
	{
		if (tk->type == TYP_AND || tk->type == TYP_OR || tk->type == TYP_PIPE)
		{
			op = tk;
			break;
		}
		prev = tk;
		tk = tk->next;
	}
	if (!op)
		return new_ast_node(TYP_WORD, convert_tokens_to_array(tk), 0);
	left_tokens = creat_new_tk(tk, op);
	right_tokens = op->next;
	if (prev)
		prev->next = NULL;
	node = new_ast_node(op->type, new_cmd(op), op->is_exp);
	node->l = build_the_tree(left_tokens);
	node->r = build_the_tree(right_tokens);
	return node;
}

t_ast *new_ast_node(t_type type, char **cmd, int exp)
{
	t_ast *node = ft_malloc(sizeof(t_ast), FT_ALLOC);
	if (!node)
		return NULL;
	node->type = type;
	node->cmd = cmd;
	node->exp = exp;
	node->l = NULL;
	node->r = NULL;
	return node;
}
