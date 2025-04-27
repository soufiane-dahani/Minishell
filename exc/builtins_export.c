/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:26:37 by sodahani          #+#    #+#             */
/*   Updated: 2025/04/26 14:43:43 by sodahani         ###   ########.fr       */
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
	while (arg[len] && arg[len] != '=' && !(arg[len] == '+' && arg[len
			+ 1] == '='))
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

static int	handle_export_arg(char *arg, char ***envp_ptr,
		t_export_store *store)
{
	if (!is_valid_env_assignment(arg) && !is_valid_identifier(arg))
	{
		ft_putstr_fd("export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("`: not a valid identifier\n", 2);
		return (1);
	}
	if (ft_strnstr(arg, "+=", ft_strlen(arg)))
		update_env_plus(arg, envp_ptr);
	else if (ft_strchr(arg, '='))
		add_or_update_env(arg, envp_ptr);
	else
		store_export_only_var(arg, store);
	remove_export_only_var(*envp_ptr, store);
	return (0);
}

int	my_export(char **args, char ***envp_ptr, t_export_store *store)
{
	int	i;

	i = 1;
	if (!args[1])
		return (print_sorted_env(*envp_ptr, store));
	while (args[i])
	{
		handle_export_arg(args[i], envp_ptr, store);
		i++;
	}
	return (0);
}
