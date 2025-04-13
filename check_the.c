/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_the.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:51:26 by yaait-am          #+#    #+#             */
/*   Updated: 2025/04/13 12:34:44 by yaait-am         ###   ########.fr       */
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
	// head = the_ast(tk, op);
	return (head);
}

t_token	*skip_the_par(t_token *tk, t_token **op)
{
	tk = creat_new(tk, op);
	return (tk);
}
