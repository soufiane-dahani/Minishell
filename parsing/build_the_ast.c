/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_the_ast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:51:26 by yaait-am          #+#    #+#             */
/*   Updated: 2025/05/11 11:41:00 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_the_exp(t_token **tk)
{
	int		i;
	t_token	*s;

	s = *tk;
	while (s)
	{
		i = 0;
		s->is_exp = 0;
		while (s->value[i])
		{
			if (s->value[i] == '$' && s->type != TYP_SQOUTE)
			{
				if (s->type == TYP_DQUOTE)
					s->is_exp = 1;
				else
					s->is_exp = 2;
				break ;
			}
			i++;
		}
		s = s->next;
	}
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

void	rediraction_to_linked_list(t_token *tk, t_token **node)
{
	t_token	*tmp;

	if (!tk || !node)
		return ;
	*node = NULL;
	tmp = tk;
	while (tmp)
	{
		if (tmp->type != TYP_RPAR)
			add_token(node, tmp->value, tmp->type, tmp->is_exp);
		tmp = tmp->next;
	}
}

t_ast	*start_for_ast(t_token *tk)
{
	t_ast	*node;
	t_token	*op;

	if (!tk)
		return (NULL);
	op = NULL;
	tk = skip_par(tk);
	the_best_sep(tk, &op);
	if (op && (is_token_sep(op->type) || op->type == TYP_LPAR))
	{
		node = ft_malloc(sizeof(t_ast), FT_ALLOC);
		if (!node)
			return (NULL);
		node->cmd = ft_malloc(sizeof(char *) * 2, FT_ALLOC);
		help_start(op, &tk, &node);
		return (node);
	}
	if (op && is_token_nor(op->type))
	{
		node = ft_malloc(sizeof(t_ast), FT_ALLOC);
		node->cmd = NULL;
		rediraction_to_linked_list(tk, &node->redir);
	}
	creat_the_cmd(&node, &tk);
	return (node);
}
