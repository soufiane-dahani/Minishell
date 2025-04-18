/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 10:11:44 by yaait-am          #+#    #+#             */
/*   Updated: 2025/04/16 17:50:00 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_space(char c)
{
	return (c == ' ' || c == '\n' || c == '\t');
}

void	nb_tok_special(char *str, int *i, int *count)
{
	char	quote;

	if (is_special_char(str[*i]) || str[*i] == '(' || str[*i] == ')')
	{
		(*count)++;
		(*i)++;
	}
	else if (str[*i] == '"' || str[*i] == '\'')
	{
		quote = str[*i];
		(*i)++;
		(*count)++;
		while (str[*i] && str[*i] != quote)
			(*i)++;
		if (str[*i] == quote)
			(*i)++;
	}
}

int	nb_tok(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && is_space(str[i]))
			i++;
		if (!str[i])
			break ;
		if (is_special_char(str[i]) || str[i] == '(' || str[i] == ')'
			|| str[i] == '"' || str[i] == '\'')
			nb_tok_special(str, &i, &count);
		else
		{
			count++;
			while (str[i] && !is_space(str[i]) && !is_special_char(str[i])
				&& str[i] != '(' && str[i] != ')'
				&& str[i] != '"' && str[i] != '\'')
				i++;
		}
	}
	return (count++, count);
}

int	is_special_char(char c)
{
	return (c == '|' || c == '&' || c == '<' || c == '>'
		|| c == '(' || c == ')');
}
