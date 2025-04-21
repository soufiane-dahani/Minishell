/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:26:37 by sodahani          #+#    #+#             */
/*   Updated: 2025/04/21 12:36:42 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_valid_env_assignment(char *arg)
{
	int	i;

	if (!arg || !arg[0])
		return (0);
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (0);
	i = 1;
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (0);
		i++;
	}
	return (arg[i] == '=');
}

static int	count_env_vars(char **envp, char **cmd, int *env_len, int *add_len)
{
	*env_len = 0;
	*add_len = 0;
	while (envp && envp[*env_len])
		(*env_len)++;
	while (cmd[*add_len + 1] && is_valid_env_assignment(cmd[*add_len + 1]))
		(*add_len)++;
	return (*env_len + *add_len);
}

static void	copy_variables(char **new_env, char **envp, char **cmd, int env_len)
{
	int	i;
	int	j;

	i = 0;
	while (i < env_len)
	{
		new_env[i] = ft_strdup(envp[i]);
		i++;
	}
	j = 0;
	while (cmd[j + 1] && is_valid_env_assignment(cmd[j + 1]))
	{
		new_env[i++] = ft_strdup(cmd[j + 1]);
		j++;
	}
	new_env[i] = NULL;
}

char	**copy_and_extend_env(char **envp, char **cmd)
{
	int		env_len;
	int		add_len;
	char	**new_env;
	int		total_len;

	total_len = count_env_vars(envp, cmd, &env_len, &add_len);
	new_env = ft_malloc(sizeof(char *) * (total_len + 1), FT_ALLOC);
	if (!new_env)
		return (NULL);
	copy_variables(new_env, envp, cmd, env_len);
	return (new_env);
}

int	my_env(char **cmd, char **envp)
{
	char	**tmp_env;
	int		i;

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
