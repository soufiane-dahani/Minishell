/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:26:37 by sodahani          #+#    #+#             */
/*   Updated: 2025/04/24 20:12:10 by sodahani         ###   ########.fr       */
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
		if (is_valid_env_assignment(args[i]))
		{
			if (!ft_strchr2(args[i], '+'))
				update_env_plus(args[i], envp_ptr);
			if (!ft_strchr2(args[i], '=') && ft_strchr2(args[i], '+'))
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
void update_env_plus(char *var, char ***envp_ptr)
{
	int	idx;

	idx = env_var_index(var, *envp_ptr);
	if (idx != -1)
	{
		(*envp_ptr)[idx] = ft_strjoin((*envp_ptr)[idx], ft_strchr(var, '=') + 1);
	}
	else
		append_env_var(var, envp_ptr);
}
char	*ft_strdup_custom2(const char *s)
{
	size_t	len;
	int		i;
	char	*copy;
	int		k;
	len = ft_strlen(s);
	copy = ft_malloc(len + 1, FT_ALLOC);
	i = 0;
	k = 0;
	if (!copy)
		return (NULL);
	while(s[i])
	{
		if (s[k] == '+')
			k++;
		if (s[k] == '\0')
			break;
		copy[i] = s[k];
		i++;
		k++;
	}
	copy[i] = '\0';
	return (copy);
}