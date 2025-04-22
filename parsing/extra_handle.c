/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:08:25 by yaait-am          #+#    #+#             */
/*   Updated: 2025/04/22 19:26:23 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_token(char c)
{
	return (c == '|' || c == '&'
			|| c == '>' || c == '<');
}

char	*extra_work(char *cmd)
{
	int		i;
	char	*new;
	int		a;
	int		j;
	char	q;

	i = 0;
	a = 0;
	j = 0;
	new = ft_malloc(ft_strlen(cmd) * sizeof(char), FT_ALLOC);
	while (cmd[i])
	{
		while (cmd[i] && cmd[i] != '\'' && cmd[i] != '"')
			i++;
		if (cmd[i])
		{
			q = cmd[i];
			new[j++] = q;
			while (cmd[a] && a < i)
				new[j++] = cmd[a++];
			i++;
			while (cmd[i] && cmd[i] != q)
				new[j++] = cmd[i++];
			i++;
			while (cmd[i] && is_space(cmd[i]))
				new[j++] = cmd[i++];
			new[j++] = q;
		}
		else
		{
			i = 0;
			while (cmd[i])
				new[j++] = cmd[i++];
		}
	}
	new[j] = '\0';
	printf("%s\n", new);
	return (new);
}
