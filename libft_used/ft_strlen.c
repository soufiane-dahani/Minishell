/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 08:15:40 by yaait-am          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/05/08 14:29:42 by yaait-am         ###   ########.fr       */
=======
/*   Updated: 2025/04/28 15:49:34 by yaait-am         ###   ########.fr       */
>>>>>>> dahani
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	ft_strlen(const char *c)
{
	size_t	i;

	i = 0;
	if (!c)
		return (0);
	while (c[i])
		i++;
	return (i);
}

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*y;

	i = 0;
	y = s;
	while (i < n)
	{
		y[i] = c;
		i++;
	}
	return (y);
}
