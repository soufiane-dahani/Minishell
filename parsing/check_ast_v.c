/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ast_v.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 15:21:32 by yaait-am          #+#    #+#             */
/*   Updated: 2025/05/01 10:37:51 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*my_getenv(char *s, char **copy)
{
	int		i;
	int		len;
	static char	**env;

	if (!env)
		env = copy;
	if (!s)
		return (NULL);
	len = ft_strlen(s);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], s, len) == 0)
			return (env[i] + len + 1);
		i++;
	}
	return (NULL);
}
