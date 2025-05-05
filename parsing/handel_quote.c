/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handel_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:40:55 by yaait-am          #+#    #+#             */
/*   Updated: 2025/05/05 07:48:22 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	store_new(char **new, int *i, char *s, int *old)
{
	int		j;
	char	*store;
	char	*env;

	j = 0;
	store = ft_malloc((ft_strlen(s) * sizeof(char)) + 1, FT_ALLOC);
	(*i)++;
	if (is_exit(new, i, s, old))
		return ;
	while (s[(*i)] && ft_isalnum(s[(*i)]))
		store [j++] = s[(*i)++];
	store[j] = '\0';
	env = my_getenv(store, NULL);
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
	(1) && (i = 0), (j = 0), (total = 0);
	while (s[i])
	{
		j = 0;
		if (s[i] == '$')
		{
			i++;
			if (s[i] == '?')
			{
				total += is_question(s, &i);
				continue ;
			}
			total += help_clcule(&env, &j, s, &i);
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
		if (!s->value)
		{
			printf("invalid syntax\n");
			return (NULL);
		}
		s = s->next;
	}
	return (tk);
}

int	handle_quote(t_cmd *data, int i)
{
	char	quote;
	int		start;

	start = i;
	while (data->s[i] && data->s[i] != '\'' && data->s[i] != '"')
		i++;
	if (!data->s[i])
		return (i - start);
	start = i;
	while (start > 0 && !is_space(data->s[start - 1])
		&& !is_special_char(data->s[start - 1]))
		start--;
	quote = data->s[i];
	i++;
	while (data->s[i] && data->s[i] != quote)
		i++;
	if (data->s[i] && data->s[i] == quote)
		i++;
	while (data->s[i] && !is_space(data->s[i]) && !is_special_char(data->s[i])
		&& data->s[i] != '"' && data->s[i] != '\'')
		i++;
	return (i - start);
}
