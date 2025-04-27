/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export_help.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:26:37 by sodahani          #+#    #+#             */
/*   Updated: 2025/04/27 20:10:10 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	store_export_only_var(const char *key, t_export_store *store)
{
	int		count;
	char	**new_vars;

	count = 0;
	while (store->vars && store->vars[count])
	{
		if (ft_strcmp(store->vars[count], key) == 0)
			return ;
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

void	remove_export_only_var(char **env, t_export_store *store)
{
	int		i;
	int		k;
	char	**new_vars;
	char	*store_name;

	if (!env || !store || !store->vars)
		return ;
	new_vars = (char **)ft_malloc(sizeof(char *) * (count_store_vars(store)
				+ 1), FT_ALLOC);
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
		i++;
	}
	new_vars[k] = NULL;
	store->vars = new_vars;
}
