/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:53:59 by yaait-am          #+#    #+#             */
/*   Updated: 2025/02/26 16:39:55 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**handle_quote(char *input)
{
	char	**scmd;
	int		len;
	int		i;
	int		a;
	char	*token;

	len = ft_strlen(input);
	scmd = malloc(100 * sizeof(char **));
	a = 0;
	i = 0;
	while (i < len)
	{
		while (is_space(input[i]))
			i++;
		token = malloc(len - i + 1);
		i = is_quote(i, input, token, len);
		scmd[a++] = token;
	}
	return (scmd);
}

int	is_quote(int i, char *input, char *token, int len)
{
	char	quote;
	int		j;

	j = 0;
	if (input[i] == '"' || input[i] == '\'')
	{
		quote = input[i++];
		while (i < len && input[i] != quote)
			token[j++] = input[i++];
		i++;
	}
	else
	{
		while (i < len && !is_space(input[i])
			&& input[i] != '"' && input[i] != '\'')
			token[j++] = input[i++];
	}
	token[j] = '\0';
	return (i);
}
