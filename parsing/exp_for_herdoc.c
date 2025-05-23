/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_for_herdoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 11:26:49 by yaait-am          #+#    #+#             */
/*   Updated: 2025/05/12 07:18:11 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	handle_exit_and_number(char **new, int *i, char *s, int *a)
{
	char	*store;
	int		j;

	j = 0;
	if (s[(*i)] == '?')
	{
		store = ft_itoa(g_exit);
		while (store[j])
			(*new)[(*a)++] = store[j++];
		(*i)++;
		return (1);
	}
	if (s[(*i)] >= '0' && s[(*i)] <= '9')
	{
		(*i)++;
		return (1);
	}
	if (!ft_isalnum(s[(*i)]))
	{
		(*new)[(*a++)] = '$';
		(*new)[(*a++)] = s[(*i++)];
		return (1);
	}
	return (0);
}

static void	more_expand(char **new, int *i, char *s, int *a)
{
	int		j;
	char	*store;
	char	*env;

	j = 0;
	store = ft_malloc((ft_strlen(s) * sizeof(char)) + 1, FT_ALLOC);
	(*i)++;
	if (!s[(*i)] || s[(*i)] == '"' || s[(*i)] == '\''
		|| (!ft_isalnum(s[(*i)]) && s[(*i)] != '?'))
	{
		(*new)[(*a)++] = '$';
		return ;
	}
	if (handle_exit_and_number(new, i, s, a))
		return ;
	while (s[(*i)] && ft_isalnum(s[(*i)]))
		store[j++] = s[(*i)++];
	store[j] = '\0';
	env = my_getenv(store, NULL);
	if (env)
	{
		j = 0;
		while (env[j])
			(*new)[(*a)++] = env[j++];
	}
}

int	its_not_between_single(char *s, int i)
{
	int	a;
	int	b;
	int	d;

	a = 0;
	b = 0;
	d = 0;
	while (s[a] && a < i)
	{
		if (s[a] == '"' && (b % 2 == 0))
			d++;
		if (s[a] == '\'' && (d % 2 == 0))
			b++;
		a++;
	}
	if ((b % 2) && (d % 2 == 0))
		return (0);
	return (1);
}

char	*exp_for_herdoc(char *s)
{
	int		i;
	int		a;
	char	*env;
	char	*new;

	i = 0;
	env = ft_malloc(ft_strlen(s) + 1, FT_ALLOC);
	a = calculate_s(s, env);
	new = ft_malloc(a * sizeof(char) + 1, FT_ALLOC);
	a = 0;
	while (s[i])
	{
		if (s[i] == '$' && its_not_between_single(s, i))
			more_expand(&new, &i, s, &a);
		else
			new[a++] = s[i++];
	}
	new[a] = '\0';
	return (new);
}

int	is_not_inside_quote(char *s, int i)
{
	int	a;
	int	b;
	int	d;

	a = 0;
	b = 0;
	d = 0;
	while (s[a] && a < i)
	{
		if (s[a] == '"')
			d++;
		if (s[a] == '\'')
			b++;
		a++;
	}
	if ((b % 2) || (d % 2))
		return (0);
	return (1);
}
