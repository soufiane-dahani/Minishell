/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 09:27:59 by yaait-am          #+#    #+#             */
/*   Updated: 2025/02/25 09:38:37 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			free(cmd_path);
			return (1);
		}
		free(cmd_path);
		i++;
	}
	return (0);
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
			return (1);
		}
		i++;
	}
	return (0);
}
