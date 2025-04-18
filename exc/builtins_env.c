/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:26:37 by sodahani          #+#    #+#             */
/*   Updated: 2025/04/18 19:50:24 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_valid_env_assignment(char *arg)
{
	int	i;

	if (!arg)
		return (0);
	i = 1;
	while (arg[i] && arg[i] != '=')
	{
		i++;
	}
	return (arg[i] == '=');
}

char	**copy_and_extend_env(char **envp, char **cmd)
{
	int		env_len;
	int		add_len;
	int		i;
	char	**new_env;
	int		j;

	env_len = 0;
	add_len = 0;
	i = 0;
	while (envp && envp[env_len])
		env_len++;
	while (cmd[add_len + 1] && is_valid_env_assignment(cmd[add_len + 1]))
		add_len++;
	new_env = ft_malloc(sizeof(char *) * (env_len + add_len + 1), FT_ALLOC);
	if (!new_env)
		return (NULL);
	i = 0;
	while (i < env_len)
	{
		new_env[i] = ft_strdup(envp[i]);
		i++;
	}
	j = 0;
	while (j < add_len)
	{
		new_env[i++] = ft_strdup(cmd[j + 1]);
		j++;
	}
	new_env[i] = NULL;
	return (new_env);
}

int	my_env(char **cmd, char **envp)
{
	char **tmp_env;
	int i;

	if (cmd[1] && !is_valid_env_assignment(cmd[1]))
	{
		ft_putstr_fd("env: invalid argument or unsupported option\n", 2);
		return (127);
	}

	tmp_env = copy_and_extend_env(envp, cmd);
	if (!tmp_env)
	{
		perror("env");
		return (1);
	}

	i = 0;
	while (tmp_env[i])
	{
		printf("%s\n", tmp_env[i]);
		i++;
	}
	return (0);
}