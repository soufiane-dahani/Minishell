/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_func_to_build_ast.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:08:10 by yaait-am          #+#    #+#             */
/*   Updated: 2025/05/07 15:27:06 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	the_best_sep(t_token *tk, t_token **op)
{
	if (lowest(&tk, TYP_OR, op))
		return ;
	else if (lowest(&tk, TYP_AND, op))
		return ;
	else if (lowest(&tk, TYP_PIPE, op))
		return ;
	else if (lowest(&tk, TYP_LPAR, op))
		return ;
	else if (lowest(&tk, TYP_REDAPP, op))
		return ;
	else if (lowest(&tk, TYP_REDHERE, op))
		return ;
	else if (lowest(&tk, TYP_REDOUT, op))
		return ;
	else if (lowest(&tk, TYP_REDIN, op))
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

void	help_start(t_token *op, t_token **tk, t_ast **node)
{
	t_token	*left;
	t_token	*right;

	if (!op || !tk || !node || !(*node))
		return ;
	left = new_list(tk, op);
	right = op->next;
	op->next = NULL;
	(*node)->l = start_for_ast(left);
	(*node)->r = start_for_ast(right);
	(*node)->cmd[0] = ft_strdup((*tk)->value);
	(*node)->cmd[1] = NULL;
	(*node)->redir = NULL;
	(*node)->exp = (*tk)->is_exp;
	(*node)->type = (*tk)->type;
}

t_token	*skip_par(t_token *tk)
{
	t_token	*start;
	t_token	*end;
	t_token	*new;

	if (!tk || !tk->next)
		return (tk);
	start = tk;
	end = tk;
	while (end->next)
		end = end->next;
	if (!is_valid_enclosure(start, end))
		return (tk);
	new = create_inner_tokens(start, end);
	return (skip_par(new));
}

int	lowest(t_token **tk, t_type h, t_token **op)
{
	t_token	*prev;
	int		count_par;
	t_token	*last_match;

	prev = *tk;
	last_match = NULL;
	count_par = 0;
	while (prev)
	{
		if (prev->type == TYP_LPAR)
			count_par++;
		if (prev->type == TYP_RPAR)
			count_par--;
		if (is_token_sep(prev->type) && count_par != 0)
		{
			prev = prev->next;
			continue ;
		}
		if (prev && prev->type == h)
			last_match = prev;
		prev = prev->next;
	}
	if (last_match)
		return (*op = last_match, 1);
	return (0);
}
