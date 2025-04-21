/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_ast.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:42:19 by yaait-am          #+#    #+#             */
/*   Updated: 2025/04/21 19:43:18 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_token_sep(t_type s)
{
	return (s == TYP_AND || s == TYP_PIPE || s == TYP_OR);
}

int	is_token_nor(t_type s)
{
	return (s == TYP_REDAPP || s == TYP_REDIN
		|| s == TYP_REDOUT || s == TYP_REDHERE);
}

void	help_fix(t_token *s, t_token **new, t_token *redir)
{
	t_token	*last;

	while (s && !is_token_sep(s->type))
	{
		add_token(new, s->value, s->type);
		s = s->next;
	}
	if (redir)
		add_token(new, redir->value, redir->type);
	redir = redir->next;
	if (redir)
		add_token(new, redir->value, redir->type);
	if (s)
	{
		add_token(new, s->value, s->type);
		s = s->next;
		if (s)
		{
			last = *new;
			while (last->next)
				last = last->next;
			last->next = fix_the_case(s);
		}
	}
}

t_token	*fix_the_case(t_token *tk)
{
	t_token	*s;
	t_token	*new;
	t_token	*redir;

	(1) && (s = tk), (new = NULL), (redir = NULL);
	while (s && !is_token_nor(s->type))
		s = s->next;
	if (!s)
		return (tk);
	s = tk;
	while (s && !is_token_sep(s->type) && !is_token_nor(s->type))
	{
		add_token(&new, s->value, s->type);
		s = s->next;
	}
	if (!s)
		return (tk);
	redir = s;
	s = s->next;
	if (s->next && !is_token_sep(s->type))
		s = s->next;
	return (help_fix(s, &new, redir), new);
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
	tk = fix_the_case(tk);
	node = start_for_ast(tk);
	return (node);
}
