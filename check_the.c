/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_the.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:51:26 by yaait-am          #+#    #+#             */
/*   Updated: 2025/04/13 17:56:05 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_the_exp(t_token *tk)
{
	int		i;
	t_token	*s;

	s = tk;
	while (s)
	{
		i = 0;
		tk->is_exp = 0;
		while (s->value[i])
		{
			if (s->value[i] == '$' && s->type != TYP_SQOUTE)
			{
				s->is_exp = 1;
				break ;
			}
			i++;
		}
		s = s->next;
	}
	if (is_cmd_valid(tk))
		return (0);
	return (1);
}

int	is_nor(t_token *tk)
{
	int		a;
	t_token	*swp;

	a = 1;
	swp = tk;
	while (swp)
	{
		if (swp->type == TYP_AND || swp->type == TYP_OR
			|| swp->type == TYP_PIPE)
			a = 0;
		swp = swp->next;
	}
	return (a);
}

t_ast	*start_for_ast(t_token *tk, t_token *op)
{
	t_ast	*head;

	head = NULL;
	if (is_nor(tk))
		return (creat_nor_cmd(tk));
	if (!op)
		tk = skip_the_par(tk, &op);
	if (tk == NULL || tk == op)
		return (NULL);
	head = the_ast(tk, op);
	return (head);
}

t_token	*skip_the_par(t_token *tk, t_token **op)
{
	tk = creat_new(tk, op);
	return (tk);
}

t_ast	*the_ast(t_token *tk, t_token *old)
{
	t_ast	*node;
	int		npar;
	t_token	*op;
	t_token	*prev;

	node = NULL;
	npar = 0;
	prev = tk;
	op = NULL;
	while (prev && prev != old)
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
		return (printf("invalid syntax\n"), NULL);
	node = start_for_ast(tk, op);
	return (node);
}
