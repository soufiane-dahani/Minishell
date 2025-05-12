/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 11:41:09 by yaait-am          #+#    #+#             */
/*   Updated: 2025/05/12 14:42:23 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	match_pattern(const char *pattern, const char *str)
{
	if (*pattern == '\0' && *str == '\0')
		return (1);
	if (*pattern == '*')
	{
		while (*pattern == '*')
			pattern++;
		if (*pattern == '\0')
			return (1);
		while (*str)
		{
			if (match_pattern(pattern, str))
				return (1);
			str++;
		}
		return (0);
	}
	if (*pattern == *str)
		return (match_pattern(pattern + 1, str + 1));
	return (0);
}

char	*skip_quote(char *s)
{
	t_quote	q;
	char	*new;

	if (!s || !s[0])
		return (s);
	q.i = 0;
	q.j = 0;
	new = ft_malloc(ft_strlen(s) + 1, FT_ALLOC);
	while (s[q.i])
	{
		if ((s[q.i] == '\'' || s[q.i] == '"') && find_close_quote(q.i, s))
		{
			q.ch = s[q.i++];
			while (s[q.i] && s[q.i] != q.ch)
				new[q.j++] = s[q.i++];
			if (s[q.i] == q.ch)
				q.i++;
		}
		else
			new[q.j++] = s[q.i++];
	}
	new[q.j] = '\0';
	return (new);
}

t_token	*change_the_cards(char *pattern)
{
	DIR				*dir;
	struct dirent	*entry;
	t_token			*expanded;

	expanded = NULL;
	dir = opendir(".");
	if (!dir)
		return (NULL);
	entry = readdir(dir);
	while (entry)
	{
		if (!(entry->d_name[0] == '.' && pattern[0] != '.'))
		{
			if (match_pattern(pattern, entry->d_name))
				add_token(&expanded, entry->d_name, TYP_WORD, 0);
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return (expanded);
}

int	is_single(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '"')
			return (0);
		if (s[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}

int	is_couple(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\'')
			return (0);
		if (s[i] == '"')
			return (1);
		i++;
	}
	return (0);
}
