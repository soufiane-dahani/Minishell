/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_exp_before_func.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:26:07 by yaait-am          #+#    #+#             */
/*   Updated: 2025/05/12 08:00:55 by yaait-am         ###   ########.fr       */
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
	t_quote	q;
	char	*env;
	char	*new;

	env = ft_malloc((ft_strlen(str) + 1) * sizeof(char), FT_ALLOC);
	q.a = calculate_s(str, env);
	q.j = 0;
	q.i = 0;
	new = ft_malloc(((sizeof(char)) * (q.a + 1)), FT_ALLOC);
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

int	help_add_match(struct dirent *entry, char **new, char *s, int *mat)
{
	int	count;

	count = 0;
	if (match_pattern(s, entry->d_name))
	{
		new[(*mat)++] = ft_strdup(entry->d_name);
		count++;
	}
	return (count);
}

char	**handle_wildcards_for_string(char **s)
{
	t_init	wild;
	int		found_match;

	found_match = 0;
	init_var_for_wlidcards(&wild, s);
	wild.i = 0;
	wild.matches = 0;
	while (s[wild.i])
	{
		wild.has_wildcard = 0;
		wild.j = 0;
		while (s[wild.i][wild.j])
			if (s[wild.i][wild.j++] == '*'
				&& is_not_inside_quote(s[wild.i], wild.j - 1))
				wild.has_wildcard = 1;
		if (wild.has_wildcard)
			add_matches(wild.new, s[wild.i], &wild.matches, &found_match);
		else
			wild.new[wild.matches++] = ft_strdup(s[wild.i]);
		wild.i++;
	}
	if (!wild.matches || !wild.new[0])
		return (s);
	wild.new[wild.matches] = NULL;
	return (wild.new);
}
