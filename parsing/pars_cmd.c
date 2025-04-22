/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 11:41:09 by yaait-am          #+#    #+#             */
/*   Updated: 2025/04/22 14:38:04 by yaait-am         ###   ########.fr       */
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
