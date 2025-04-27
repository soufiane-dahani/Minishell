/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 11:41:09 by yaait-am          #+#    #+#             */
/*   Updated: 2025/04/27 10:50:52 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	match_pattern(const char *pattern, const char *str)
{
	if (*pattern == '\0' && *str == '\0')
		return (1);
	if (*pattern == '*')
		return (match_pattern(pattern + 1, str)
			|| (*str && match_pattern(pattern, str + 1)));
	if (*pattern == *str)
		return (match_pattern(pattern + 1, str + 1));
	return (0);
}

char	*skip_quote(char *s)
{
	t_quote		q;
	char		*new;

	q.i = 0;
	q.j = 0;
	q.a = 0;
	new = ft_malloc(ft_strlen(s) * sizeof(char) + 1, FT_ALLOC);
	help_skiping(&new, &q, s);
	if (!s[q.i])
		return (s);
	q.ch = s[q.i++];
	while (s[q.i])
	{
		if (s[q.i] == q.ch)
		{
			q.a++;
			q.i++;
			if (!s[q.i])
				break ;
		}
		new [q.j++] = s[q.i++];
	}
	if (!(q.a % 2))
		return (NULL);
	return (new[q.j] = '\0', new);
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
