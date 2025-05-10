/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:26:37 by sodahani          #+#    #+#             */
/*   Updated: 2025/05/10 19:04:25 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	add_new_env(char *key, char *value, char ***envp)
{
	int		count;
	char	*new_entry;
	char	**new_env;
	char	**old_env;

	count = count_env_entries(envp);
	if (!create_and_copy_env(envp, &new_env, count))
		return (0);
	new_entry = ft_strjoin3(key, "=", value);
	if (!new_entry)
	{
		return (0);
	}
	new_env[count] = new_entry;
	new_env[count + 1] = NULL;
	old_env = *envp;
	*envp = new_env;
	return (1);
}

static int	update_env(char *key, char *value, char ***envp)
{
	if (!envp || !*envp || !key || !value)
		return (0);
	if (update_existing_env(key, value, envp))
		return (1);
	return (add_new_env(key, value, envp));
}

static char	*get_cd_target(char **cmd, char ***envp)
{
	char	*target;

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
		if (cmd[1])
			ft_putstr_fd("cd: OLDPWD not set\n", 2);
		else
			ft_putstr_fd("cd: HOME not set\n", 2);
	}
	return (target);
}

int	my_cd(char **cmd, char ***envp)
{
	char	*target;
	char	*oldpwd;

	if (cmd[2])
		return(ft_putstr_fd(" too many arguments\n", 2), 1);
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
	{
		perror("cd: getcwd");
		return (1);
	}
	target = get_cd_target(cmd, envp);
	if (!target)
	{
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
		return (1);
	}
	if (getcwd(cwd, sizeof(cwd)))
	{
		update_env("OLDPWD", oldpwd, envp);
		update_env("PWD", cwd, envp);
	}
	return (0);
}
