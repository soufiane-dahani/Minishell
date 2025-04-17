/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 15:21:06 by yaait-am          #+#    #+#             */
/*   Updated: 2025/03/03 12:25:37 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t	ft_count(char const *s, char c)
{
	size_t	i;
	int		j;

	i = 0;
	j = 0;
	while (*s)
	{
		if (*s == c)
			j = 0;
		else if (!j)
		{
			j = 1;
			i++;
		}
		s++;
	}
	return (i);
}

static char	*ft_cpy(char const *s, char c)
{
	size_t		i;
	char		*word;
	size_t		j;
	const char	*sir;

	i = 0;
	j = 0;
	sir = s;
	while (s[i] && s[i] != c)
		i++;
	word = (char *)ft_malloc ((i + 1) * sizeof(char), FT_ALLOC);
	if (!word)
		return (NULL);
	while (j < i)
	{
		word[j] = sir[j];
		j++;
	}
	word[i] = '\0';
	return (word);
}

static void	free_all(char **ar, size_t c)
{
	size_t	i;

	i = 0;
	while (i < c)
	{
		free(ar[i]);
		i++;
	}
	free(ar);
}

static char	**ft_null(char const *s, char c)
{
	size_t	words;
	char	**yas;

	if (!s)
		return (NULL);
	words = ft_count(s, c);
	yas = (char **) ft_malloc ((words + 1) * sizeof(char *), FT_ALLOC);
	if (!yas)
		return (NULL);
	return (yas);
}

char	**ft_split(char const *s, char c)
{
	char	**yas;
	size_t	i;

	yas = ft_null(s, c);
	if (!yas)
		return (NULL);
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			yas[i] = ft_cpy(s, c);
			if (!yas[i])
				return (free_all(yas, i), NULL);
			i++;
			while (*s && *s != c)
				s++;
		}
		else
			s++;
	}
	yas[i] = NULL;
	return (yas);
}
