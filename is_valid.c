/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 09:27:59 by yaait-am          #+#    #+#             */
/*   Updated: 2025/02/26 16:08:38 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_args(t_cmd *data)
{
	if (!strcmp(data->all[0], "cd") && (!data->all[1] || data->all[2]))
	{
		printf("cd: wrong number of arguments\n");
		return (0);
	}
	if (!strcmp(data->all[0], "export") && !data->all[1])
	{
		printf("export: missing argument\n");
		return (0);
	}
	if (!strcmp(data->all[0], "unset") && !data->all[1])
	{
		printf("unset: missing argument\n");
		return (0);
	}
	return (1);
}

int	check_is_valid(t_cmd *data)
{
	int		i;
	char	*path_env;
	char	**paths;
	char	*cmd_path;

	if (is_built(data))
		return (1);
	path_env = getenv("PATH");
	if (!path_env)
		return (0);
	paths = ft_split(path_env, ':');
	i = 0;
	while (paths[i])
	{
		cmd_path = ft_strjoin(ft_strjoin(paths[i], "/"), data->all[0]);
		if (access(cmd_path, X_OK) == 0)
		{
			printf("\n[ ==> valid command (found in PATH) <== ]\n\n");
			return (free(cmd_path), 1);
		}
		free(cmd_path);
		i++;
	}
	printf("bash: %s: command not found\n", data->all[0]);
	return (free(paths), 0);
}

int	is_built(t_cmd *data)
{
	const char	*builtins[8];
	int			i;

	builtins[0] = "cd";
	builtins[1] = "echo";
	builtins[2] = "pwd";
	builtins[3] = "export";
	builtins[4] = "unset";
	builtins[5] = "env";
	builtins[6] = "exit";
	builtins[7] = NULL;
	i = 0;
	while (builtins[i])
	{
		if (!strcmp(data->all[0], builtins[i]))
		{
			printf("\n[ ==> valid comond (built) <== ]\n\n");
			is_valid_args(data);
			return (1);
		}
		i++;
	}
	return (0);
}
