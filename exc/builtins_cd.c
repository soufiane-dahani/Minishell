/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:26:37 by sodahani          #+#    #+#             */
/*   Updated: 2025/04/18 09:09:04 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	update_env(char *key, char *value, char ***envp)
{
	int		i;
	int		count;
	char	*new_entry;
	int		key_len;
	char	**new_env;

	key_len = ft_strlen(key);
	new_entry = ft_strjoin3(key, "=", value);
	if (!new_entry)
		return ;
	i = 0;
	while ((*envp)[i])
	{
		if (!ft_strncmp((*envp)[i], key, key_len) && (*envp)[i][key_len] == '=')
		{
			free((*envp)[i]);
			(*envp)[i] = new_entry;
			return ;
		}
		i++;
	}
	count = 0;
	while ((*envp)[count])
		count++;
	new_env = ft_malloc(sizeof(char *) * (count + 2), FT_ALLOC);
	if (!new_env)
		return ;
	i = 0;
	while (i < count)
	{
		new_env[i] = (*envp)[i];
		i++;
	}
	new_env[count] = new_entry;
	new_env[count + 1] = NULL;
	*envp = new_env;
}

int	my_cd(char **cmd, char **envp)
{
	char	*target;
	char	cwd[1024];
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
	{
		perror("cd: getcwd");
		return (1);
	}
	if (!cmd[1])
	{
		target = getenv("HOME");
		if (!target)
		{
			ft_putstr_fd("cd: HOME not set\n", 2);
			free(oldpwd);
			return (1);
		}
	}
	else
		target = cmd[1];
	if (chdir(target) != 0)
	{
		perror("cd");
		free(oldpwd);
		return (1);
	}
	if (getcwd(cwd, sizeof(cwd)))
	{
		update_env("OLDPWD", oldpwd, &envp);
		update_env("PWD", cwd, &envp);
	}
	free(oldpwd);
	return (0);
}
