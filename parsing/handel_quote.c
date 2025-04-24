/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handel_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:40:55 by yaait-am          #+#    #+#             */
/*   Updated: 2025/04/24 09:26:01 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isalnum(int c)
{
	return ((c >= 'A' && c <= 'Z')
		|| (c >= 'a' && c <= 'z')
		|| (c >= '0' && c <= '9'));
}

void	store_new(char **new, int *i, char *s, int *old)
{
	int		j;
	char	*store;
	char	*env;

	j = 0;
	store = ft_malloc((ft_strlen(s) * sizeof(char)) + 1, FT_ALLOC);
	(*i)++;
	if (!s[(*i)] || s[(*i)] == '"')
	{
		(*new)[(*old)++] = '$';
		return ;
	}
	while (s[(*i)] && ft_isalnum(s[(*i)]))
		store [j++] = s[(*i)++];
	store[j] = '\0';
	env = getenv(store);
	if (env)
	{
		j = 0;
		while (env[j])
			(*new)[(*old)++] = env[j++];
	}
}

int	calculate_s(char *s, char *env)
{
	int (i), (total), (j);
	i = 0;
	j = 0;
	total = 0;
	while (s[i])
	{
		j = 0;
		if (s[i] == '$')
		{
			i++;
			while (s[i] && ft_isalnum(s[i]))
				env[j++] = s[i++];
			env[j] = '\0';
			if (j > 0)
				total += ft_strlen(getenv(env));
		}
		else
		{
			i++;
			total++;
		}
	}
	return (total);
}

char	*new_with_exp(char *s)
{
	int		i;
	char	*new;
	int		a;
	int		j;
	char	*env;

	if (!s)
		return (NULL);
	a = 0;
	env = ft_malloc(ft_strlen(s) * sizeof(char) + 1, FT_ALLOC);
	j = 0;
	i = calculate_s(s, env);
	new = ft_malloc(((sizeof(char)) * i) + 1, FT_ALLOC);
	i = 0;
	while (s[j])
	{
		if (s[j] == '$')
			store_new(&new, &j, s, &i);
		else
			new[i++] = s[j++];
	}
	new[i] = '\0';
	return (new);
}

t_token	*handle_exp_quote(t_token *tk)
{
	t_token	*s;
	int		i;

	s = tk;
	i = 0;
	while (s)
	{
		i = 0;
		while (s->value[i])
		{
			if (s->value[i] == '$' && s->value[1] && s->type != TYP_SQOUTE)
				s->value = new_with_exp(s->value);
			i++;
		}
		s->value = skip_quote(s->value);
		s = s->next;
	}
	return (tk);
}
