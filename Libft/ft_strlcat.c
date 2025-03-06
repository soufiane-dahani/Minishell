/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 10:35:27 by sodahani          #+#    #+#             */
/*   Updated: 2024/11/03 15:05:10 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	ret;
	size_t	j;

	i = 0;
	ret = 0;
	if (dstsize == 0 && !dst)
		return (ft_strlen(src));
	ret = ft_strlen(dst);
	if (dstsize == 0 || dstsize <= ret)
		return (ft_strlen(src) + dstsize);
	j = ret;
	while (src[i] && j < dstsize - 1)
		dst[j++] = src[i++];
	dst[j] = '\0';
	return (ret + ft_strlen(src));
}
