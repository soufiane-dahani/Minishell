/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:26:37 by sodahani          #+#    #+#             */
/*   Updated: 2025/04/28 21:31:41 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

long	ft_atol(const char *str)
{
	long	res;
	int		sign;

	res = 0;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str && *str >= '0' && *str <= '9')
		res = res * 10 + (*str++ - '0');
	return (res * sign);
}

int	my_exit(char **cmd)
{
	int	ex;

	ft_putstr_fd("exit\n", STDERR_FILENO);
	if (cmd[1])
	{
		if (!is_numeric(cmd[1]))
		{
			ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
			ft_malloc(0, FT_CLEAR);
			exit(2);
		}
		if (cmd[2])
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			return (1);
		}
		ex = atoi(cmd[1]);
		ft_malloc(0, FT_CLEAR);
		exit(ex);
	}
	ft_malloc(0, FT_CLEAR);
	exit(0);
}

int	create_and_copy_env(char ***envp, char ***new_env, int count)
{
	int	i;

	*new_env = ft_malloc(sizeof(char *) * (count + 2), FT_ALLOC);
	if (!*new_env)
		return (0);
	i = 0;
	while (i < count)
	{
		(*new_env)[i] = ft_strdup((*envp)[i]);
		if (!(*new_env)[i])
		{
			return (0);
		}
		i++;
	}
	return (1);
}
