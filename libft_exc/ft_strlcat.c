/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 10:35:27 by sodahani          #+#    #+#             */
/*   Updated: 2025/04/26 17:31:17 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
