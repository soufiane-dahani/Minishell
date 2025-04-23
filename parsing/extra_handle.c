/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:08:25 by yaait-am          #+#    #+#             */
/*   Updated: 2025/04/23 16:52:35 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_token(char c)
{
	return (c == '|' || c == '&'
		|| c == '>' || c == '<'
		|| is_space(c));
}

void	more_extra(char **new, t_q *quote, char *s)
{
	char	q;

	if ((is_token(s[(quote->i)])))
	{
		(quote->i) = quote->a;
		while (s[(quote->i)] && !is_token(s[(quote->i)]))
			(*new)[quote->j++] = s[(quote->i)++];
	}
	else
	{
		q = s[(quote->i)];
		(*new)[quote->j++] = q;
		while (s[quote->a] && quote->a < (quote->i))
			(*new)[quote->j++] = s[quote->a++];
		(quote->i)++;
		while (s[(quote->i)] && s[(quote->i)] != q)
			(*new)[quote->j++] = s[(quote->i)++];
		if (s[(quote->i)] && is_token(s[(quote->i) + 1]))
		{
			(quote->i)++;
			while (s[(quote->i)] && (is_token(s[(quote->i)])))
				(*new)[quote->j++] = s[(quote->i)++];
			(*new)[quote->j++] = q;
		}
	}
}

char	*extra_work(char *s)
{
	t_q		q;
	char	*new;

	q.a = 0;
	q.i = 0;
	q.j = 0;
	new = ft_malloc(strlen(s) * sizeof(char) + 1, FT_ALLOC);
	while (s[q.i])
	{
		while (s[q.i] && (is_token(s[q.i])))
			new[q.j++] = s[q.i++];
		q.a = q.i;
		while (s[q.i] && s[q.i] != '\'' && s[q.i] != '"' && !is_token(s[q.i]))
			q.i++;
		if (!s[q.i])
		{
			q.i = q.a;
			while (s[q.i])
				new[q.j++] = s[q.i++];
		}
		else
			more_extra(&new, &q, s);
	}
	new[q.i] = '\0';
	return (new);
}

int	get_env_len(char *str)
{
	int i = 0;
	while (str[i] && (isalnum(str[i]) || str[i] == '_'))
	i++;
	return i;
}

char	*before_quote(char *str)
{
	int		i = 0, j = 0;
	char	*env = ft_malloc(ft_strlen(str + 1), FT_ALLOC);
	char	*new = ft_malloc(calculate_s(str, env) + 1, FT_ALLOC);

	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && str[i + 1] != '"' && str[i + 1] != ' ')
		{
			i++; // skip $
			int var_len = get_env_len(&str[i]);
			char varname[256];
			strncpy(varname, &str[i], var_len);
			varname[var_len] = '\0';
			env = getenv(varname);
			if (env)
			{
				for (int k = 0; env[k]; k++)
					new[j++] = env[k];
			}
			i += var_len;
		}
		else
		{
			new[j++] = str[i++];
		}
	}
	new[j] = '\0';
	return new;
}
