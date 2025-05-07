/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_exp_before_func.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:26:07 by yaait-am          #+#    #+#             */
/*   Updated: 2025/05/07 17:00:40 by yaait-am         ###   ########.fr       */
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

void	add_matches(char **new, char *pattern, int *matches)
{
	DIR				*dir;
	struct dirent	*entry;
	int				show_hidden;
	int				is_dir;

	show_hidden = (pattern[0] == '.');
	is_dir = 0;
	if (ft_strchr(pattern, '/'))
		is_dir = 1;
	dir = opendir(".");
	if (!dir)
		return ;
	entry = readdir(dir);
	while (entry)
	{
		if (!show_hidden && entry->d_name[0] == '.')
			entry = readdir(dir);
		if (is_dir && entry->d_type != DT_DIR)
			entry = readdir(dir);
		if (match_pattern(pattern, entry->d_name))
			new[(*matches)++] = ft_strdup(entry->d_name);
		entry = readdir(dir);
	}
	closedir(dir);
}

char	**handle_wildcards_for_string(char **s)
{
	char	**new;
	int		i;
	int		j;
	int		matches;
	int		has_wildcard;

	new = ft_malloc(sizeof(char *) * (count_entries() + 1), FT_ALLOC);
	if (!new)
		return (s);
	(1) && (i = 0), (matches = 0);
	while (s[i])
	{
		(1) && (has_wildcard = 0), (j = 0);
		while (s[i][j])
			if (s[i][j++] == '*')
				has_wildcard = 1;
		if (has_wildcard)
			add_matches(new, s[i], &matches);
		else
			new[matches++] = ft_strdup(s[i]);
		i++;
	}
	if (!matches || !new[0])
		return (s);
	return (new[matches] = NULL, new);
}
