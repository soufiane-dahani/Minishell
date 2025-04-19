/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:26:37 by sodahani          #+#    #+#             */
/*   Updated: 2025/04/19 10:27:43 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_env_var(int idx, char *new_var, char ***envp_ptr)
{
	(*envp_ptr)[idx] = ft_strdup_custom(new_var);
}

int	env_var_index(char *arg, char **env)
{
	int		i = 0;
	int		len = 0;

	while (arg[len] && arg[len] != '=')
		len++;

	while (env[i])
	{
		if (!ft_strncmp(env[i], arg, len) && env[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}


// Add new env var
void	append_env_var(char *new_var, char ***envp_ptr)
{
	int		len = 0;
	char	**new_env;
	int		i;

	while ((*envp_ptr)[len])
		len++;
	new_env = ft_malloc(sizeof(char *) * (len + 2), FT_ALLOC);
	if (!new_env)
		return;
	i = 0;
	while (i < len)
	{
		new_env[i] = (*envp_ptr)[i];
		i++;
	}
	new_env[len] = ft_strdup_custom(new_var);
	new_env[len + 1] = NULL;
	*envp_ptr = new_env;
}

// Final add_or_update_env
void	add_or_update_env(char *arg, char ***envp_ptr)
{
	int	idx;

	idx = env_var_index(arg, *envp_ptr);
	if (idx != -1)
		update_env_var(idx, arg, envp_ptr);
	else
		append_env_var(arg, envp_ptr);
}

int	my_export(char **args, char ***envp_ptr)
{
	int	i = 1;

	if (!args[1])
		return (print_sorted_env(*envp_ptr));

	while (args[i])
	{
		if (is_valid_env_assignment(args[i]) || is_valid_identifier(args[i]))
			add_or_update_env(args[i], envp_ptr);
		else
		{
			ft_putstr_fd("export: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("`: not a valid identifier\n", 2);
		}
		i++;
	}
	return (0);
}
