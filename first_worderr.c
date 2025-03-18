/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_worderr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:24:37 by yaait-am          #+#    #+#             */
/*   Updated: 2025/03/18 14:27:07 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_root(char *cmd)
{
	int		i;
	char	*cd;

	if (!cmd)
		return (0);
	i = ft_strlen(cmd);
	if (cmd[0] == '/' || cmd[0] == '-')
	{
		printf("bash: %s: command not found\n", cmd);
		return (1);
	}
	if (cmd[0] == '\\')
	{
		if (i % 2)
			return (1);
		cd = ft_malloc((i / 2) + 1, FT_ALLOC);
		if (!cd)
			return (1);
		ft_memset(cd, '\\', i / 2);
		cd[i / 2] = '\0';
		printf("bash: %s: command not found\n", cd);
		free(cd);
		return (1);
	}
	return (0);
}
