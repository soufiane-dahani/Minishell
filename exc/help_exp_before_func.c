/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_exp_before_func.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:26:07 by yaait-am          #+#    #+#             */
/*   Updated: 2025/05/10 10:01:10 by yaait-am         ###   ########.fr       */
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
	t_init	wild;

	wild.s_count = 0;
	while (s[wild.s_count])
		wild.s_count++;
	wild.entries = count_entries();
	if (wild.entries < wild.s_count)
		wild.entries = wild.s_count;
	wild.new = ft_malloc(sizeof(char *) * (wild.entries + 1), FT_ALLOC);
	(1) && (wild.i = 0), (wild.matches = 0);
	while (s[wild.i])
	{
		(1) && (wild.has_wildcard = 0), (wild.j = 0);
		while (s[wild.i][wild.j])
			if (s[wild.i][wild.j++] == '*')
				wild.has_wildcard = 1;
		if (wild.has_wildcard)
			add_matches(wild.new, s[wild.i], &wild.matches);
		else
			wild.new[wild.matches++] = ft_strdup(s[wild.i]);
		wild.i++;
	}
	if (!wild.matches || !wild.new[0])
		return (s);
	return (wild.new[wild.matches] = NULL, wild.new);
}
