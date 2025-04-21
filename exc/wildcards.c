/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:26:37 by sodahani          #+#    #+#             */
/*   Updated: 2025/04/21 11:37:37 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// char	**expand_wildcard(const char *pattern)
// {
// 	DIR				*dir;
// 	struct dirent	*entry;
// 	char			**matches;
// 	int				i;

// 	dir = opendir(".");
// 	matches = malloc(sizeof(char *) * 1024);
// 	i = 0;
// 	if (!dir)
// 		return (NULL);
// 	while ((entry = readdir(dir)) != NULL)
// 	{
// 		if (match_pattern(pattern, entry->d_name))
// 		{
// 			matches[i++] = ft_strdup(entry->d_name);
// 		}
// 	}
// 	matches[i] = NULL;
// 	closedir(dir);
// 	return (matches);
// }
