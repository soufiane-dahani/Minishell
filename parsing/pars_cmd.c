/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 11:41:09 by yaait-am          #+#    #+#             */
/*   Updated: 2025/04/23 10:02:27 by yaait-am         ###   ########.fr       */
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
	int		i;
	int		j;
	char	*new;
	char	quote;

	if (s[0] != '\'' || s[0] != '"')
		return (ft_strdup(s));
	i = 1;
	j = 0;
	quote = s[0];
	new = ft_malloc(ft_strlen(s) * sizeof(char) + 1, FT_ALLOC);
	while (s[i] && s[i] != quote)
		new[j++] = s[i++];
	new[j] = '\0';
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
