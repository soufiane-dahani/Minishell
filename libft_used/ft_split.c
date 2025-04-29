/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 15:21:06 by yaait-am          #+#    #+#             */
/*   Updated: 2025/04/25 15:11:40 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check(char h, char *charset)
{
	int	i;

	i = 0;
	while (charset[i] != '\0')
	{
		if (h == charset[i])
			return (1);
		i++;
	}
	return (0);
}

static int	ft_strlen_spl(char *str, char *charset)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && !check(str[i], charset))
		i++;
	return (i);
}

static int	count(char *str, char *charset)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	while (str[i] != '\0')
	{
		while (str[i] != '\0' && check(str[i], charset))
			i++;
		if (str[i] != '\0')
			y++;
		while (str[i] != '\0' && !check(str[i], charset))
			i++;
	}
	return (y);
}

static char	*ft_strdup_spl(char *src, char *charset)
{
	char	*yas;
	int		i;
	int		sir;

	i = 0;
	sir = ft_strlen_spl(src, charset);
	yas = ft_malloc (sizeof(char) * (sir + 1), FT_ALLOC);
	if (!yas)
		return (NULL);
	while (i < sir)
	{
		yas[i] = src[i];
		i++;
	}
	yas[i] = '\0';
	return (yas);
}

char	**ft_split2(char *str, char *charset)
{
	char	**yas;
	int		i;
	int		j;

	i = 0;
	j = 0;
	yas = ft_malloc(sizeof(char *) * (count(str, charset) + 1), FT_ALLOC);
	if (!yas)
		return (NULL);
	while (str[j] != '\0')
	{
		while (str[j] != '\0' && check(str[j], charset))
			j++;
		if (str[j] != '\0')
		{
			yas[i] = ft_strdup_spl(&str[j], charset);
			i++;
		}
		while (str[j] != '\0' && !check(str[j], charset))
			j++;
	}
	yas[i] = 0;
	return (yas);
}
