/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_fun2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:26:37 by sodahani          #+#    #+#             */
/*   Updated: 2025/04/19 11:38:57 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env_size(char **envp)
{
	int i = 0;
	while (envp[i])
		i++;
	return (i);
}

void	swap_strs(char **a, char **b)
{
	char *tmp = *a;
	*a = *b;
	*b = tmp;
}

// Simple Bubble Sort
void	sort_env(char **env)
{
	int		i, j;
	int		size = ft_env_size(env);

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (ft_strcmp(env[j], env[j + 1]) > 0)
				swap_strs(&env[j], &env[j + 1]);
			j++;
		}
		i++;
	}
}

int	print_sorted_env(char **envp)
{
	int		i = 0;
	char	**copy;

	copy = ft_malloc(sizeof(char *) * (ft_env_size(envp) + 1), FT_ALLOC);
	if (!copy)
		return (1);
	while (envp[i])
	{
		copy[i] = ft_strdup_custom(envp[i]);
		i++;
	}
	copy[i] = NULL;
	sort_env(copy);
	i = 0;
	while (copy[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(copy[i], 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
	return (0);
}
