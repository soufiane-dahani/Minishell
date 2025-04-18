/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ast_v.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 15:21:32 by yaait-am          #+#    #+#             */
/*   Updated: 2025/04/18 17:05:07 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_ast_is_valid(void)
{
	t_ast	*cheker;

	cheker = g_ast;
	while (cheker)
	{
		if ((cheker->type == TYP_AND || cheker->type == TYP_PIPE
				|| cheker->type == TYP_OR) && (!cheker->r || !cheker->l))
		{
			printf("invalid syntax near `%s'\n", cheker->cmd[0]);
			return (0);
		}
		cheker = cheker->l;
	}
	cheker = g_ast;
	while (cheker)
	{
		if ((cheker->type == TYP_AND || cheker->type == TYP_PIPE
				|| cheker->type == TYP_OR) && (!cheker->r || !cheker->l))
		{
			printf("invalid syntax near `%s'\n", cheker->cmd[0]);
			return (0);
		}
		cheker = cheker->r;
	}
	return (1);
}
