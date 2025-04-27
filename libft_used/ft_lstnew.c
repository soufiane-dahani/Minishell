/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 14:56:48 by yaait-am          #+#    #+#             */
/*   Updated: 2025/04/27 11:14:54 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*yas;

	yas = malloc(sizeof(t_list));
	if (!yas)
		return (NULL);
	yas->content = content;
	yas->next = NULL;
	return (yas);
}

static int	ft_count(long nb)
{
	int	i;

	i = 1;
	if (nb < 0)
	{
		nb = -nb;
		i++;
	}
	while (nb / 10)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		i;
	char	*yas;
	long	nb;

	nb = n;
	i = ft_count(nb);
	yas = ft_malloc ((i + 1) * sizeof(char), FT_ALLOC);
	if (!yas)
		return (NULL);
	yas[i] = '\0';
	if (nb < 0)
	{
		yas[0] = '-';
		nb = -nb;
	}
	i = i - 1;
	if (nb == 0)
		yas[i] = '0';
	while (nb > 0)
	{
		yas[i] = (nb % 10) + '0';
		nb /= 10;
		i--;
	}
	return (yas);
}
