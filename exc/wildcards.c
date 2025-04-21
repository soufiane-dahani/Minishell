/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:26:37 by sodahani          #+#    #+#             */
/*   Updated: 2025/04/21 18:47:54 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool match_pattern(const char *pattern, const char *str)
{
	if (*pattern == '\0' && *str == '\0')
		return true;
	if (*pattern == '*')
		return match_pattern(pattern + 1, str) || (*str && match_pattern(pattern, str + 1));
	if (*pattern == *str)
		return match_pattern(pattern + 1, str + 1);
	return false;
}

char	*expand_wildcard(const char *pattern)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*result;
	char			*tmp;
	int				first = 1;

	dir = opendir(".");
	if (!dir)
		return (NULL);

	result = ft_strdup("");

	while ((entry = readdir(dir)) != NULL)
	{
		if (entry->d_name[0] == '.')
			continue;
		
		if (match_pattern(pattern, entry->d_name))
		{
			if (first)
			{
				free(result);
				result = ft_strdup(entry->d_name);
				first = 0;
			}
			else
			{
				tmp = result;
				result = ft_strjoin(tmp, " ");
				free(tmp);
				tmp = result;
				result = ft_strjoin(tmp, entry->d_name);
				free(tmp);
			}
		}
	}
	closedir(dir);
	return (result);
}

