/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_building_ast.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:42:19 by yaait-am          #+#    #+#             */
/*   Updated: 2025/05/04 11:35:40 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_token_nor(t_type s)
{
	return (s == TYP_REDAPP || s == TYP_REDIN
		|| s == TYP_REDOUT || s == TYP_REDHERE);
}

void	store_typ_no_red(t_token **tmp, t_token **redir, t_token **new)
{
	while ((*tmp) && !is_token_sep((*tmp)->type))
	{
		if (is_token_nor((*tmp)->type))
		{
			add_token(redir, (*tmp)->value, (*tmp)->type, (*tmp)->is_exp);
			(*tmp) = (*tmp)->next;
			if ((*tmp) && ((*tmp)->type == TYP_WORD
					|| (*tmp)->type == TYP_DQUOTE
					|| (*tmp)->type == TYP_SQOUTE))
				add_token(redir, (*tmp)->value, (*tmp)->type, (*tmp)->is_exp);
			else
				add_token(new, (*tmp)->value, (*tmp)->type, (*tmp)->is_exp);
		}
		else
			add_token(new, (*tmp)->value, (*tmp)->type, (*tmp)->is_exp);
		(*tmp) = (*tmp)->next;
	}
	while ((*redir))
	{
		add_token(new, (*redir)->value, (*redir)->type, (*redir)->is_exp);
		(*redir) = (*redir)->next;
	}
}

t_token	*fix_the_case(t_token *tk)
{
	t_token	*redir;
	t_token	*new;
	t_token	*tmp;
	t_token	*head;

	if (!tk)
		return (NULL);
	redir = NULL;
	new = NULL;
	tmp = tk;
	while (tmp && !is_token_nor(tmp->type))
		tmp = tmp->next;
	if (!tmp)
		return (tk);
	tmp = tk;
	store_typ_no_red(&tmp, &redir, &new);
	if (tmp)
	{
		add_token(&new, tmp->value, tmp->type, tmp->is_exp);
		head = new;
		while (head->next)
			head = head->next;
		head->next = fix_the_case(tmp->next);
	}
	return (new);
}

t_ast	*build_the_tree(t_token *tk)
{
	t_ast	*node;
	int		npar;
	t_token	*op;
	t_token	*prev;

	node = NULL;
	npar = 0;
	prev = tk;
	op = NULL;
	while (prev)
	{
		if (prev->type == TYP_LPAR)
			npar++;
		if (prev->type == TYP_RPAR)
			npar--;
		if ((prev->type == TYP_AND || prev->type == TYP_PIPE
				|| prev->type == TYP_OR) && npar == 0)
			op = prev;
		prev = prev->next;
	}
	if (npar != 0)
		return (printf("invalid syntax near `('\n"), NULL);
	tk = fixing(tk);
	node = start_for_ast(tk);
	return (node);
}
