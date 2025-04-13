/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_new_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 12:21:21 by yaait-am          #+#    #+#             */
/*   Updated: 2025/04/13 14:59:44 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*find_the_head(t_token *tk)
{
	t_token	*cur;
	int		npar;
	t_token	*op;

	if (!tk)
		return (NULL);
	npar = 0;
	if (tk->type == TYP_LPAR)
		tk = tk->next;
	cur = tk;
	while (cur)
	{
		if (cur->type == TYP_LPAR)
			npar++;
		if (cur->type == TYP_RPAR)
			npar--;
		if ((cur->type == TYP_AND || cur->type == TYP_PIPE
				|| cur->type == TYP_OR) && npar == 1)
			op = cur;
		cur = cur->next;
	}
	return (op);
}

t_token	*creat_new(t_token *tk, t_token **op)
{
	t_token	*head;
	t_token	*cur_node;
	t_token	*cur;

	*op = find_the_head(tk);
	if (!tk)
		return (NULL);
	head = NULL;
	if (tk->type == TYP_LPAR)
		tk = tk->next;
	cur = tk;
	while (cur)
	{
		if (cur->type == TYP_RPAR && !cur->next)
			break ;
		ft_new_node(&head, &cur_node, cur);
		cur = cur->next;
	}
	return (head);
}

void	ft_new_node(t_token **head, t_token **cur_node, t_token *cur)
{
	t_token	*tmp;

	*cur_node = create_token(cur->value, cur->type);
	if (!*cur_node)
		return ;
	if (!*head)
		*head = *cur_node;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = *cur_node;
	}
}
