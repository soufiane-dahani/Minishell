/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_the_cmd_valid.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 14:23:23 by yaait-am          #+#    #+#             */
/*   Updated: 2025/03/10 15:08:21 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	is_cmd_valid(char **cmd)
{
	// int	i;
	// i = 0;
	if (!check_the_first(cmd))
		return ;
	// while (cmd[i])
	// {
	// 	i++;
	// }
}

int	check_the_first(char **cmd)
{
	if (!ft_strncmp(cmd[0], "|", 2) && !ft_strncmp(cmd[1], "&", 2))
	{
		printf("bash: syntax error near unexpected token `|&'\n");
		return (0);
	}
	if (is_dnear_error(cmd))
	{
		printf("bash: syntax error near unexpected token `%s'\n", cmd[1]);
		return (0);
	}
	if (is_error_near(cmd))
	{
		printf("bash: syntax error near unexpected token `%s'\n", cmd[0]);
		return (0);
	}
	if (is_newline(cmd))
	{
		printf("bash: syntax error near unexpected token `newline'\n");
		return (0);
	}
	if (is_root(cmd[0]))
		return (0);
	return (1);
}

int	is_newline(char **cmd)
{
	if (!ft_strncmp(cmd[0], "&&", 3) || !ft_strncmp(cmd[0], "||", 3)
		|| (!ft_strncmp(cmd[0], "|", 2) && ft_strncmp(cmd[1], "&", 2))
		|| !ft_strncmp(cmd[0], "&", 2))
		return (0);
	if ((!ft_strncmp(cmd[0], ">", 2) && ft_strncmp(cmd[1], ">", 2)))
		return (1);
	if ((!ft_strncmp(cmd[0], "<", 2) && ft_strncmp(cmd[1], "<", 2)))
		return (1);
	if ((!ft_strncmp(cmd[0], "<<", 2) && ft_strncmp(cmd[1], "<<", 2))
		&& ft_strncmp(cmd[1], "<", 2) && ft_strncmp(cmd[1], ">", 2)
		&& ft_strncmp(cmd[1], ">>", 2))
		return (1);
	if ((!ft_strncmp(cmd[0], ">>", 2) && ft_strncmp(cmd[1], ">>", 2))
		&& ft_strncmp(cmd[1], "<", 2) && ft_strncmp(cmd[1], ">", 2)
		&& ft_strncmp(cmd[1], "<<", 2))
		return (1);
	return (0);
}

int	is_error_near(char **cmd)
{
	if ((!ft_strncmp(cmd[0], ">", 2) && !ft_strncmp(cmd[1], ">", 2))
		|| (!ft_strncmp(cmd[0], ">>", 2) && !ft_strncmp(cmd[1], ">>", 2)))
		return (1);
	if ((!ft_strncmp(cmd[0], "<", 2) && !ft_strncmp(cmd[1], "<", 2))
		|| (!ft_strncmp(cmd[0], "<<", 2) && !ft_strncmp(cmd[1], "<<", 2)))
		return (1);
	return (0);
}

int	is_dnear_error(char **cmd)
{
	if (!ft_strncmp(cmd[0], ">>", 2) && (!ft_strncmp(cmd[1], ">>", 2)
			|| !ft_strncmp(cmd[1], ">", 2) || !ft_strncmp(cmd[1], "<", 2)
			|| !ft_strncmp(cmd[1], "<<", 2)))
		return (1);
	if (!ft_strncmp(cmd[0], "<<", 2) && (!ft_strncmp(cmd[1], ">>", 2)
			|| !ft_strncmp(cmd[1], ">", 2) || !ft_strncmp(cmd[1], "<", 2)
			|| !ft_strncmp(cmd[1], "<<", 2)))
		return (1);
	return (0);
}
