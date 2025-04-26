/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:26:37 by sodahani          #+#    #+#             */
/*   Updated: 2025/04/26 14:23:59 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_env_var(int idx, char *new_var, char ***envp_ptr)
{
	(*envp_ptr)[idx] = ft_strdup_custom(new_var);
}

int	env_var_index(char *arg, char **env)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (arg[len] && arg[len] != '=' && !(arg[len] == '+' && arg[len + 1] == '='))
		len++;
	while (env[i])
	{
		if (!ft_strncmp(env[i], arg, len) && env[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}


void	append_env_var(char *new_var, char ***envp_ptr)
{
	int		len;
	char	**new_env;
	int		i;

	len = 0;
	while ((*envp_ptr)[len])
		len++;
	new_env = ft_malloc(sizeof(char *) * (len + 2), FT_ALLOC);
	if (!new_env)
		return ;
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

void add_or_update_env(char *arg, char ***envp_ptr)
{
	int idx;
	char *clean_arg;

	clean_arg = remove_plus(arg);
	idx = env_var_index(clean_arg, *envp_ptr);
	if (idx != -1)
	{
		(*envp_ptr)[idx] = ft_strdup_custom(clean_arg);
	}
	else
		append_env_var(clean_arg, envp_ptr);
}

int	my_export(char **args, char ***envp_ptr, t_export_store *store)
{
	int	i;

	i = 1;
	if (!args[1])
		return (print_sorted_env(*envp_ptr, store));
	while (args[i])
	{
		if (is_valid_env_assignment(args[i]) || is_valid_identifier(args[i]))
		{
			if (ft_strnstr(args[i], "+=", ft_strlen(args[i])))
				update_env_plus(args[i], envp_ptr);
			else if (ft_strchr(args[i], '='))
				add_or_update_env(args[i], envp_ptr);
			else
				store_export_only_var(args[i], store);
			remove_export_only_var(*envp_ptr, store);
		}
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

