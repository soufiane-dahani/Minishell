/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:26:37 by sodahani          #+#    #+#             */
/*   Updated: 2025/05/03 17:25:25 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

unsigned int	ft_rand(void)
{
	unsigned int	num;
	int				fd;

	num = 0;
	fd = open("/dev/urandom", O_RDONLY);
	if (fd < 0)
		return (42);
	if (read(fd, &num, sizeof(num)) != sizeof(num))
		num = 1337;
	close(fd);
	return (num);
}


char	*random_str(void)
{
	int		length;
	char	*str;
	int		i;

	length = 5 + (ft_rand() % 11);
	str = ft_malloc(length + 1, FT_ALLOC);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (i < length)
	{
		str[i] = 'a' + (ft_rand() % 26);
		i++;
	}
	str[length] = '\0';
	return (str);
}
