/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_worderr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:24:37 by yaait-am          #+#    #+#             */
/*   Updated: 2025/03/20 14:42:48 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_the_first(t_token *tk)
{
	if (!tk)
		return (0);
	if (invalid_syntax(tk))
	{
		printf("invalid syntax near '%s'\n", tk->value);
		return (0);
	}
	return (1);
}

int	invalid_syntax(t_token *tk)
{
	if (tk->type != TYP_WORD && tk->type != TYP_LPAR)
		return (1);
	if (tk->value[0] == '&' && tk->value[1] == '\0')
		return (1);
	return (0);
}

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
