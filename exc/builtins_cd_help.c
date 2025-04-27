/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd_help.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:26:37 by sodahani          #+#    #+#             */
/*   Updated: 2025/04/27 16:23:17 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_value(char **envp, const char *name)
{
	int	i;
	int	name_len;

	if (!envp || !name)
		return (NULL);
	name_len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], name, name_len) && envp[i][name_len] == '=')
			return (envp[i] + name_len + 1);
		i++;
	}
	return (NULL);
}

int	find_env_index(char **envp, const char *name)
{
	int	i;
	int	name_len;

	if (!envp || !name)
		return (-1);
	name_len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], name, name_len) && envp[i][name_len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

char	*expand_tilde(char *path, char **envp)
{
	char	*home;

	if (!path || path[0] != '~')
		return (ft_strdup(path));
	home = get_env_value(envp, "HOME");
	if (!home)
		return (ft_strdup(path));
	if (path[1] == '\0')
		return (ft_strdup(home));
	if (path[1] == '/')
		return (ft_strjoin(home, path + 1));
	return (ft_strdup(path));
}

int	update_existing_env(char *key, char *value, char ***envp)
{
	int		index;
	char	*new_entry;

	index = find_env_index(*envp, key);
	if (index == -1)
		return (0);
	new_entry = ft_strjoin3(key, "=", value);
	if (!new_entry)
		return (0);
	// free((*envp)[index]);
	(*envp)[index] = new_entry;
	return (1);
}

int	count_env_entries(char ***envp)
{
	int	count;

	count = 0;
	while ((*envp)[count])
		count++;
	return (count);
}
