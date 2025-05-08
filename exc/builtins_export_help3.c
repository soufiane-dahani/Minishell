/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export_help3.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:26:37 by sodahani          #+#    #+#             */
/*   Updated: 2025/05/08 20:15:08 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	print_env_variables(char **vars)
{
	int	i;

	i = 0;
	if (!vars)
		return ;
	while (vars[i])
	{
		print_env_line(vars[i]);
		i++;
	}
}

static char	**copy_environment(char **envp)
{
	int		i;
	char	**copy;

	i = 0;
	copy = ft_malloc(sizeof(char *) * (ft_env_size(envp) + 1), FT_ALLOC);
	if (!copy)
		return (NULL);
	while (envp[i])
	{
		copy[i] = ft_strdup_custom(envp[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

int	print_sorted_env(char **envp, t_export_store *store)
{
	char	**env_copy;
	char	**store_vars;

	env_copy = copy_environment(envp);
	if (!env_copy)
		return (1);
	sort_env(env_copy);
	print_env_variables(env_copy);
	store_vars = NULL;
	if (store)
		store_vars = store->vars;
	print_env_variables(store_vars);
	return (0);
}
