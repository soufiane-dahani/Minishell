/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:26:37 by sodahani          #+#    #+#             */
/*   Updated: 2025/04/21 21:48:28 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	my_echo(char **cmd)
{
	int	i;
	int	flag;

	flag = 0;
	i = 1;
	if (cmd[1] == NULL)
	{
		printf("\n");
		return (0);
	}
	if (cmd[1][0] == '-' && cmd[1][1] == 'n' && cmd[1][2] == '\0')
	{
		flag = 1;
		i = 2;
	}
	while (cmd[i] != NULL)
	{
		printf("%s", cmd[i]);
		i++;
	}
	if (flag == 0)
		printf("\n");
	return (0);
}
