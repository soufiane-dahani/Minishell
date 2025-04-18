/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_ast.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:42:19 by yaait-am          #+#    #+#             */
/*   Updated: 2025/04/18 15:47:16 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	node = start_for_ast(tk);
	return (node);
}
