/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:08:10 by yaait-am          #+#    #+#             */
/*   Updated: 2025/04/16 15:15:42 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	the_best_sep(t_token *tk, t_token **op)
{
	if (lowest(tk, TYP_OR, op))
		return ;
	else if (lowest(tk, TYP_AND, op))
		return ;
	else if (lowest(tk, TYP_PIPE, op))
		return ;
}

static t_token	*new_list(t_token **tk, t_token *op)
{
	t_token	*start;
	t_token	*current;
	t_token	*prev;

	start = *tk;
	current = *tk;
	prev = NULL;
	while (current && current != op)
	{
		prev = current;
		current = current->next;
	}
	if (current == op)
	{
		if (prev)
			prev->next = NULL;
		else
			start = NULL;
	}
	*tk = current;
	return (start);
}

void	help_start(t_token *op, t_token *tk, t_ast **node)
{
	t_token	*left;
	t_token	*right;

	left = new_list(&tk, op);
	right = op->next;
	op->next = NULL;
	(*node)->l = start_for_ast(left);
	(*node)->r = start_for_ast(right);
	(*node)->cmd[0] = ft_strdup(tk->value);
	(*node)->cmd[1] = NULL;
	(*node)->exp = tk->is_exp;
	(*node)->type = tk->type;
}

int	lowest(t_token *tk, t_type h, t_token **op)
{
	t_token	*prev;

	prev = tk;
	while (prev)
	{
		if (prev->type == h)
		{
			*op = prev;
			(*op)->head = 1;
			return (1);
		}
		prev = prev->next;
	}
	return (0);
}
