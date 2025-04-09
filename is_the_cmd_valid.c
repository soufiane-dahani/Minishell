/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_the_cmd_valid.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 14:23:23 by yaait-am          #+#    #+#             */
/*   Updated: 2025/04/09 15:37:15 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_cmd_valid(t_token *tk)
{
	t_token	*s;

	s = tk;
	if (!check_the_first(tk))
		return (0);
	g_ast = build_the_tree(tk);
	if (!g_ast)
		return (0);
	return (1);
}
