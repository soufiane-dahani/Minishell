/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:26:37 by sodahani          #+#    #+#             */
/*   Updated: 2025/04/24 15:50:56 by sodahani         ###   ########.fr       */
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

void	add_or_update_env(char *arg, char ***envp_ptr)
{
	int	idx;

	idx = env_var_index(arg, *envp_ptr);
	if (idx != -1)
		update_env_var(idx, arg, envp_ptr);
	else
		append_env_var(arg, envp_ptr);
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
			if (!ft_strchr2(args[i], '='))
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

void	store_export_only_var(const char *key, t_export_store *store)
{
	int		count = 0;
	char	**new_vars;

	while (store->vars && store->vars[count])
	{
		if (ft_strcmp(store->vars[count], key) == 0)
			return;
		count++;
	}

	
	count = 0;
	while (store->vars && store->vars[count])
		count++;

	new_vars = ft_malloc(sizeof(char *) * (count + 2), FT_ALLOC);
	if (!new_vars)
		return ;

	count = 0;
	while (store->vars && store->vars[count])
	{
		new_vars[count] = store->vars[count];
		count++;
	}
	new_vars[count++] = ft_strdup(key);
	new_vars[count] = NULL;

	free(store->vars);
	store->vars = new_vars;
}

static char	*extract_var_name(char *var)
{
	char	*eq_pos;
	char	*name;
	int		name_len;

	if (!var)
		return (NULL);
	eq_pos = ft_strchr(var, '=');
	if (!eq_pos)
		return (ft_strdup(var));
	name_len = eq_pos - var;
	name = (char *)ft_malloc(sizeof(char) * (name_len + 1), FT_ALLOC);
	if (!name)
		return (NULL);
	ft_strlcpy(name, var, name_len + 1);
	return (name);
}

static int	is_var_in_env(char *var_name, char **env)
{
	int		i;
	char	*env_name;
	int		result;

	i = 0;
	result = 0;
	while (env[i])
	{
		env_name = extract_var_name(env[i]);
		if (env_name && ft_strcmp(var_name, env_name) == 0)
			result = 1;
		//free(env_name);
		if (result)
			break ;
		i++;
	}
	return (result);
}

static int	count_store_vars(t_export_store *store)
{
	int	count;

	count = 0;
	while (store->vars[count])
		count++;
	return (count);
}

// static void	free_store_vars(t_export_store *store)
// {
// 	int	i;

// 	i = 0;
// 	while (store->vars[i])
// 	{
// 		free(store->vars[i]);
// 		i++;
// 	}
// 	free(store->vars);
// }

void	remove_export_only_var(char **env, t_export_store *store)
{
	int		i;
	int		k;
	char	**new_vars;
	char	*store_name;

	if (!env || !store || !store->vars)
		return ;
	new_vars = (char **)ft_malloc(sizeof(char *) * (count_store_vars(store) + 1), FT_ALLOC);
	if (!new_vars)
		return ;
	i = 0;
	k = 0;
	while (store->vars[i])
	{
		store_name = extract_var_name(store->vars[i]);
		if (store_name && !is_var_in_env(store_name, env))
		{
			new_vars[k++] = ft_strdup(store->vars[i]);
		}
		free(store_name);
		i++;
	}
	new_vars[k] = NULL;
	//free_store_vars(store);
	store->vars = new_vars;
}
