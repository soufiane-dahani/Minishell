/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_the.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:51:26 by yaait-am          #+#    #+#             */
/*   Updated: 2025/04/16 15:17:42 by yaait-am         ###   ########.fr       */
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

static char	**tokens_to_cmd_array(t_token *tk)
{
	int		count;
	t_token	*tmp;
	char	**cmd;
	int		i;

	count = 0;
	tmp = tk;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	cmd = malloc(sizeof(char *) * (count + 1));
	if (!cmd)
		return (NULL);
	tmp = tk;
	i = 0;
	while (tmp)
	{
		cmd[i++] = strdup(tmp->value);
		tmp = tmp->next;
	}
	cmd[i] = NULL;
	return (cmd);
}

t_ast	*start_for_ast(t_token *tk)
{
	t_ast	*node;
	t_token	*op;

	if (!tk)
		return (NULL);
	op = NULL;
	the_best_sep(tk, &op);
	if (op)
	{
		node = ft_malloc(sizeof(t_ast), FT_ALLOC);
		if (!node)
			return (NULL);
		node->cmd = ft_malloc(sizeof(char *) * 2, FT_ALLOC);
		help_start(op, tk, &node);
		return (node);
	}
	node = ft_malloc(sizeof(t_ast), FT_ALLOC);
	if (!node)
		return (NULL);
	node->l = NULL;
	node->r = NULL;
	node->cmd = tokens_to_cmd_array(tk);
	return (node);
}
