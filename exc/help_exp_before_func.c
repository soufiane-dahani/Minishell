/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_exp_before_func.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:26:07 by yaait-am          #+#    #+#             */
/*   Updated: 2025/05/04 16:44:15 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	for_quote(t_quote *q, char *str, char **new)
{
	if (str[q->j] == '"' || str[q->j] == '\'')
	{
		q->ch = str[q->j];
		(*new)[q->i++] = str[q->j++];
		while (str[q->j] && str[q->j] != q->ch)
			(*new)[q->i++] = str[q->j++];
		if (str[q->j] == q->ch)
			(*new)[q->i++] = str[q->j++];
	}
}

void	help_quoute(char *str, char **new, t_quote *q)
{
	if (str[q->j] == '\'')
	{
		(*new)[q->i++] = str[q->j++];
		while (str[q->j] && str[q->j] != '\'')
			(*new)[q->i++] = str[q->j++];
		if (str[q->j] == '\'')
			(*new)[q->i++] = str[q->j++];
	}
	if (str[q->j] == '$' && str[q->j + 1] != '"')
		store_new(new, &q->j, str, &q->i);
	else
	{
		if (str[q->j] != '$')
			(*new)[q->i++] = str[q->j++];
		else
			q->j++;
	}
}

char	*before_quote(char *str)
{
	t_quote		q;
	char		*env;
	char		*new;

	env = ft_malloc(ft_strlen(str) * sizeof(char) + 1, FT_ALLOC);
	q.a = calculate_s(str, env);
	q.j = 0;
	q.i = 0;
	new = ft_malloc(((sizeof(char)) * q.a) + 1, FT_ALLOC);
	while (str[q.j])
	{
		if (str[q.j] && (str[q.j] == '"' || str[q.j] == '\''))
			for_quote(&q, str, &new);
		else
			help_quoute(str, &new, &q);
	}
	new[q.i] = '\0';
	return (new);
}
