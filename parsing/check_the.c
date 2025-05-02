/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_the.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:51:26 by yaait-am          #+#    #+#             */
/*   Updated: 2025/05/02 15:27:14 by yaait-am         ###   ########.fr       */
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

void rediraction_to_linked_list(t_token *tk, t_token **node)
{
	t_token *tmp;

	if (!tk || !node)
		return;
	// *node = ft_malloc(sizeof(t_token), FT_ALLOC);
	*node = NULL;
	tmp = tk;
	while (tmp)
	{
		add_token(node, tmp->value, tmp->type, tmp->is_exp);
		tmp = tmp->next;
	}
}

static char	**tokens_to_cmd_array(t_token *tk)
{
	int		count;
	t_token	*tmp;
	char	**cmd;
	int		i;

	count = 0;
	tmp = tk;
	while (tmp && tmp == TYP_WORD)
	{
		count++;
		tmp = tmp->next;
	}
	cmd = ft_malloc(sizeof(char *) * (count + 1), FT_ALLOC);
	if (!cmd)
		return (NULL);
	tmp = tk;
	i = 0;
	while (tmp && tmp->type == TYP_WORD)
	{
		if (tmp->type != TYP_RPAR)
			cmd[i++] = ft_strdup(tmp->value);
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
	if (op && (is_token_sep(op->type) || op->type == TYP_LPAR))
	{
		node = ft_malloc(sizeof(t_ast), FT_ALLOC);
		if (!node)
			return (NULL);
		node->cmd = ft_malloc(sizeof(char *) * 2, FT_ALLOC);
		help_start(op, &tk, &node);
		return (node);
	}
	if (op && op->type != TYP_WORD)
	{
		node = ft_malloc(sizeof(t_ast), FT_ALLOC);
		node->cmd = NULL;
		rediraction_to_linked_list(tk, &node->redir);
	}
	node = ft_malloc(sizeof(t_ast), FT_ALLOC);
	if (!node)
		return (NULL);
	node->l = NULL;
	node->r = NULL;
	// node->redir = NULL;
	node->cmd = tokens_to_cmd_array(tk);
	node->exp = tk->is_exp;
	node->type = tk->type;
	while (tk && tk->type == TYP_WORD)
		tk = tk->next;
	while (tk)
	{
		add_token(&node->redir, tk->value, tk->type, tk->is_exp);
		tk = tk->next;
	}
	return (node);
}
