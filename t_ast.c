/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_ast.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:42:19 by yaait-am          #+#    #+#             */
/*   Updated: 2025/04/14 15:46:52 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*creat_node(char *cmd, int exp, t_type type)
{
	t_ast	*node;

	if (!cmd)
		return (NULL);
	node = ft_malloc(sizeof(t_ast), FT_ALLOC);
	if (!node)
		return (NULL);
	node->cmd = ft_malloc(sizeof(char *) * 2, FT_ALLOC);
	if (!node->cmd)
		return (NULL);
	node->cmd[0] = ft_strdup(cmd);
	if (!node->cmd[0])
		return (NULL);
	node->cmd[1] = NULL;
	node->exp = exp;
	node->type = type;
	node->next = NULL;
	node->l = NULL;
	node->r = NULL;
	return (node);
}

t_ast	*creat_nor_cmd(t_token *tk)
{
	t_ast	*head;
	t_ast	*cur_node;
	t_token	*cur;

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
		ft_node(&head, &cur_node, cur);
		cur = cur->next;
	}
	return (head);
}

void	ft_node(t_ast **head, t_ast **cur_node, t_token *cur)
{
	t_ast	*tmp;

	*cur_node = creat_node(cur->value, cur->is_exp, cur->type);
	if (!*cur_node)
		return ;
	if (!*head)
	{
		*head = *cur_node;
		(*head)->nor = 1;
	}
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = *cur_node;
	}
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
		return (printf("invalid syntax\n"), NULL);
	node = start_for_ast(tk);
	return (node);
}

t_ast	*new_ast_node(t_type type, char **cmd, int exp)
{
	t_ast	*node;

	node = ft_malloc(sizeof(t_ast), FT_ALLOC);
	if (!node)
		return (NULL);
	node->type = type;
	node->cmd = cmd;
	node->exp = exp;
	node->l = NULL;
	node->r = NULL;
	return (node);
}
