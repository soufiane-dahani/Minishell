/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:26:37 by sodahani          #+#    #+#             */
/*   Updated: 2025/04/18 11:41:41 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * Gets value of an environment variable from envp.
 * Returns NULL if variable is not found.
 */
static char	*get_env_value(char **envp, const char *name)
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

/**
 * Finds an environment variable and returns its index or -1 if not found
 */
static int	find_env_index(char **envp, const char *name)
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

/**
 * Expands tilde (~) in path if present at the beginning
 */
static char	*expand_tilde(char *path, char **envp)
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

/**
 * Updates existing environment variable
 */
static int	update_existing_env(char *key, char *value, char ***envp)
{
	int		index;
	char	*new_entry;

	index = find_env_index(*envp, key);
	if (index == -1)
		return (0);
	new_entry = ft_strjoin3(key, "=", value);
	if (!new_entry)
		return (0);
	free((*envp)[index]);
	(*envp)[index] = new_entry;
	return (1);
}

/**
 * Adds new environment variable
 */
static int	add_new_env(char *key, char *value, char ***envp)
{
	int		i;
	int		count;
	char	*new_entry;
	char	**new_env;

	count = 0;
	while ((*envp)[count])
		count++;
	new_env = ft_malloc(sizeof(char *) * (count + 2), FT_ALLOC);
	if (!new_env)
		return (0);
	i = 0;
	while (i < count)
	{
		new_env[i] = (*envp)[i];
		i++;
	}
	new_entry = ft_strjoin3(key, "=", value);
	if (!new_entry)
	{
		free(new_env);
		return (0);
	}
	new_env[count] = new_entry;
	new_env[count + 1] = NULL;
	*envp = new_env;
	return (1);
}

/**
 * Updates or adds an environment variable
 */
static int	update_env(char *key, char *value, char ***envp)
{
	if (!envp || !*envp || !key || !value)
		return (0);
	if (update_existing_env(key, value, envp))
		return (1);
	return (add_new_env(key, value, envp));
}

/**
 * Implementation of the cd command
 */
int	my_cd(char **cmd, char ***envp)
{
	char	*target;
	char	*oldpwd;
	char	cwd[1024];

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
	{
		perror("cd: getcwd");
		return (1);
	}
	if (!cmd[1])
		target = get_env_value(*envp, "HOME");
	else if (ft_strcmp(cmd[1], "-") == 0)
	{
		target = get_env_value(*envp, "OLDPWD");
		if (target)
			printf("%s\n", target);
	}
	else
		target = cmd[1];
	if (!target)
	{
		ft_putstr_fd(cmd[1] ? "cd: OLDPWD not set\n" : "cd: HOME not set\n", 2);
		free(oldpwd);
		return (1);
	}
	if (handle_cd_chdir(target, oldpwd, cmd, envp))
	{
		free(oldpwd);
		return (1);
	}
	free(oldpwd);
	return (0);
}

/**
 * Handles the directory change portion of cd
 */
int	handle_cd_chdir(char *target, char *oldpwd, char **cmd, char ***envp)
{
	char	*expanded_path;
	char	cwd[1024];

	expanded_path = NULL;
	if (cmd[1] && cmd[1][0] == '~')
		expanded_path = expand_tilde(cmd[1], *envp);
	else
		expanded_path = ft_strdup(target);
	if (!expanded_path)
		return (1);
	if (chdir(expanded_path) != 0)
	{
		perror("cd");
		free(expanded_path);
		return (1);
	}
	free(expanded_path);
	if (getcwd(cwd, sizeof(cwd)))
	{
		update_env("OLDPWD", oldpwd, envp);
		update_env("PWD", cwd, envp);
	}
	return (0);
}

/**
 * Creates a deep copy of the environment variables
 */
char	**copy_env(char **env)
{
	int		i;
	int		count;
	char	**new_env;

	if (!env)
		return (NULL);
	count = 0;
	while (env[count])
		count++;
	new_env = ft_malloc(sizeof(char *) * (count + 1), FT_ALLOC);
	if (!new_env)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env[i])
		{
			while (--i >= 0)
				free(new_env[i]);
			free(new_env);
			return (NULL);
		}
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}