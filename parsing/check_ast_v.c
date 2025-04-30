/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ast_v.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 15:21:32 by yaait-am          #+#    #+#             */
/*   Updated: 2025/04/30 09:46:17 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*my_getenv(char *s)
{
	int		i;
	int		len;

	if (!s || !g_ast || !g_ast->env)
		return (NULL);
	len = ft_strlen(s);
	i = 0;
	while (g_ast->env[i])
	{
		if (ft_strncmp(g_ast->env[i], s, len) == 0)
			return (g_ast->env[i] + len + 1);
		i++;
	}
	return (NULL);
}
