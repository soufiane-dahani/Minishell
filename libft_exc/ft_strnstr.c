/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 10:52:38 by sodahani          #+#    #+#             */
/*   Updated: 2025/04/26 17:48:50 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int		i;
	size_t	needle_len;

	needle_len = ft_strlen(needle);
	if (ft_strlen(haystack) < len && haystack)
		len = ft_strlen(haystack);
	i = 0;
	while (len - i > 0)
	{
		if (!ft_strlen(haystack) || len - i < needle_len)
			break ;
		if (ft_strncmp(haystack + i++, needle, needle_len) == 0)
			return ((char *)(haystack + i - 1));
	}
	if (needle[0] == 0)
		return ((char *)(haystack));
	return (NULL);
}
