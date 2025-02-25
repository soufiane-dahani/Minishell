/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 09:21:49 by yaait-am          #+#    #+#             */
/*   Updated: 2025/02/25 09:23:55 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	if (!dest || !src)
		return (NULL);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!dest || !src)
		return (NULL);
	while (dest[i])
		i++;
	while (src[j])
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}

char	*ft_strdup(char *src)
{
	char	*yas;
	int		i;
	int		j;

	if (!src)
		return (NULL);
	i = ft_strlen(src);
	yas = malloc(i + 1);
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

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*yas;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	yas = malloc(j + i + 1);
	if (!yas)
		return (free(s1), s1 = NULL, NULL);
	ft_strcpy(yas, s1);
	ft_strcat(yas, s2);
	free (s1);
	return (yas);
}
