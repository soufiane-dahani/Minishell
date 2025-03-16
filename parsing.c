/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 10:09:07 by yaait-am          #+#    #+#             */
/*   Updated: 2025/03/11 11:23:41 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	more_parsing(t_cmd *data)
{
	t_spl	spl;

	spl.i = 0;
	spl.token_count = 0;
	data->cmd = ft_malloc(100 * sizeof(char *), FT_ALLOC);
	while (data->s[spl.i])
	{
		while (is_space(data->s[spl.i]))
			spl.i++;
		if (!data->s[spl.i])
			break ;
		spl.start = &data->s[spl.i];
		if (data->s[spl.i] == '"' || data->s[spl.i] == '\'')
			spl.offset = handle_quote(data, spl.i);
		else
			spl.offset = handle_token(data, &spl);
		spl.i += spl.offset;
		spl.len = &data->s[spl.i] - spl.start;
		if (spl.len > 0 && !is_special_char(data->s[spl.i - spl.offset]))
			data->cmd[spl.token_count++] = ft_strndup(spl.start, spl.len);
	}
	data->cmd[spl.token_count] = NULL;
}

int	handle_token(t_cmd *data, t_spl *spl)
{
	int (i), (start);
	i = spl->i;
	if (data->s[i] == '|' && data->s[i + 1] == '|')
	{
		data->cmd[spl->token_count++] = ft_strndup("||", 2);
		return (2);
	}
	else if (data->s[i] == '|')
	{
		data->cmd[spl->token_count++] = ft_strndup("|", 1);
		return (1);
	}
	else if (data->s[i] == '>' && data->s[i + 1] == '>')
	{
		data->cmd[spl->token_count++] = ft_strndup(">>", 2);
		return (2);
	}
	start = ft_handle_token(data, spl, &i);
	if (start > 0)
		return (start);
	start = i;
	while (data->s[i] && !is_space(data->s[i]) && !is_special_char(data->s[i]))
		i++;
	return (i - start);
}

int	ft_handle_token(t_cmd *data, t_spl *spl, int *i)
{
	if (data->s[*i] == '<' && data->s[*i + 1] == '<')
	{
		data->cmd[spl->token_count++] = ft_strndup("<<", 2);
		return (2);
	}
	else if (data->s[*i] == '>')
	{
		data->cmd[spl->token_count++] = ft_strndup(">", 1);
		return (1);
	}
	else if (data->s[*i] == '<')
	{
		data->cmd[spl->token_count++] = ft_strndup("<", 1);
		return (1);
	}
	else if (data->s[*i] == '&' && data->s[*i + 1] == '&')
	{
		data->cmd[spl->token_count++] = ft_strndup("&&", 2);
		return (2);
	}
	else if (data->s[*i] == '&')
		return (data->cmd[spl->token_count++] = ft_strndup("&", 1), 1);
	return (0);
}

int	handle_quote(t_cmd *data, int i)
{
	char	quote;
	int		start;

	start = i;
	quote = data->s[i++];
	while (data->s[i] && data->s[i] != quote)
	{
		if (data->s[i] == '\\' && data->s[i + 1] && quote == '"')
			i++;
		i++;
	}
	if (data->s[i] == quote)
		i++;
	return (i - start);
}
