/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_the.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:51:26 by yaait-am          #+#    #+#             */
/*   Updated: 2025/03/20 14:11:54 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_the_exp(t_token *tk)
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
	is_cmd_valid(tk);
}
