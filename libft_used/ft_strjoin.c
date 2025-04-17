/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 09:59:38 by yaait-am          #+#    #+#             */
/*   Updated: 2025/03/10 14:42:17 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strcpy(char *dest, char const *src)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static char	*ft_strcat(char *dest, char const *src)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (dest[i])
	{
		i++;
	}
	while (src[j])
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*yas;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	yas = ft_malloc(((j + i + 1) * sizeof(char)), FT_ALLOC);
	if (!yas)
		return (NULL);
	ft_strcpy(yas, s1);
	ft_strcat(yas, s2);
	return (yas);
}

char	*ft_strdup(const char *src)
{
	char	*yas;
	size_t	i;
	size_t	j;

	i = ft_strlen(src);
	yas = ft_malloc((i + 1), FT_ALLOC);
	if (!yas)
		return (NULL);
	j = 0;
	while (j < i)
	{
		yas[j] = src[j];
		j++;
	}
	yas[i] = '\0';
	return (yas);
}
