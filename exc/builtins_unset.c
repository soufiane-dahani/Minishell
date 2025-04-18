/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:26:37 by sodahani          #+#    #+#             */
/*   Updated: 2025/04/18 20:26:22 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_valid_identifier(char *name)
{
	int	i = 0;

	if (!name || !name[0])
		return (0);
	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (0);
	i = 1;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	env_var_index(char *name, char **env)
{
	int	i = 0;
	int	len = ft_strlen(name);

	while (env[i])
	{
		if (!ft_strncmp(env[i], name, len) && env[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

void	remove_env_var(int idx, char ***envp_ptr)
{
	int		i = 0;
	int		j = 0;
	int		count = 0;
	char	**env = *envp_ptr;
	char	**new_env;

	while (env[count])
		count++;

    new_env = ft_malloc((sizeof(char *) * count) ,FT_ALLOC);
	if (!new_env)
		return;

	while (env[i])
	{
		if (i != idx)
			new_env[j++] = ft_strdup(env[i]);
		i++;
	}
	new_env[j] = NULL;

	i = 0;
	while (env[i])
		free(env[i++]);
	free(env);

	*envp_ptr = new_env;
}

int	my_unset(char **args, char ***envp_ptr)
{
	int	i = 1;
	int	idx;

	while (args[i])
	{
		if (is_valid_identifier(args[i]))
		{
			idx = env_var_index(args[i], *envp_ptr);
			if (idx != -1)
				remove_env_var(idx, envp_ptr);
		}
		else
		{
			ft_putstr_fd("unset: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("`: not a valid identifier\n", 2);
		}
		i++;
	}
	return (0);
}
