/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:26:37 by sodahani          #+#    #+#             */
/*   Updated: 2025/05/10 18:51:52 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	my_pwd(char **env)
{
	int	i = 0;
	char	cwd[1024];

	while (env[i])
	{
		if (strncmp(env[i], "PWD=", 4) == 0)
		{
			printf("%s\n", env[i] + 4);
			return (0);
		}
		i++;
	}
	if (!getcwd(cwd, sizeof(cwd)))
	{
		perror("pwd");
		return (1);
	}
	printf("%s\n", cwd);
	return (0);
}

static int	count_env_variables(char **env)
{
	int	count;

	count = 0;
	while (env[count])
		count++;
	return (count);
}

static int	copy_env_strings(char **new_env, char **env, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env[i])
		{
			return (0);
		}
		i++;
	}
	new_env[i] = NULL;
	return (1);
}

char	**copy_env(char **env)
{
	int		count;
	char	**new_env;

	if (!env)
		return (NULL);
	count = count_env_variables(env);
	new_env = ft_malloc(sizeof(char *) * (count + 1), FT_ALLOC);
	if (!new_env)
		return (NULL);
	if (!copy_env_strings(new_env, env, count))
		return (NULL);
	return (new_env);
}
