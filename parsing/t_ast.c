/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_ast.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:42:19 by yaait-am          #+#    #+#             */
/*   Updated: 2025/04/29 09:23:13 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_token_nor(t_type s)
{
	return (s == TYP_REDAPP || s == TYP_REDIN
		|| s == TYP_REDOUT || s == TYP_REDHERE);
}

void	extra_help(t_token **new, t_token *s)
{
	t_token	*last;

	add_token(new, s->value, s->type, 0);
	s = s->next;
	if (s)
	{
		last = *new;
		while (last->next)
			last = last->next;
		last->next = fix_the_case(s);
	}
}

void	help_fix(t_token *s, t_token **new, t_token *redir)
{
	while (s && !is_token_sep(s->type) && !is_token_nor(s->type))
	{
		add_token(new, s->value, s->type, 0);
		s = s->next;
	}
	if (redir)
	{
		add_token(new, redir->value, redir->type, 0);
		redir = redir->next;
		if (redir)
			add_token(new, redir->value, redir->type, 0);
	}
	while (s && is_token_nor(s->type))
	{
		add_token(new, s->value, s->type, 0);
		s = s->next;
		if (s)
		{
			add_token(new, s->value, s->type, 0);
			s = s->next;
		}
	}
	if (s)
		extra_help(new, s);
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
		add_token(&new, s->value, s->type, 0);
		s = s->next;
	}
	if (!s)
		return (tk);
	if (s->next && !is_token_sep(s->type))
	{
		redir = s;
		s = s->next;
		s = s->next;
	}
	help_fix(s, &new, redir);
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
