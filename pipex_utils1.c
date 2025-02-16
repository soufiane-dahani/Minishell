/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 10:15:00 by sodahani          #+#    #+#             */
/*   Updated: 2025/02/16 15:06:30 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	usage(void)
{
	printf("Error: Bad argument");
	printf("Ex: ./pipex <file1> <cmd1> <cmd2> <...> <file2>\n");
	printf("    ./pipex \"here_doc\" <LIMITER> <cmd> <cmd1> <...> <file>\n");
	exit(1);
}

void	error(void)
{
	perror("Error");
	exit(126);
}

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;

	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PATH=", 5) == 0)
		i++;
	if (!envp[i])
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	path = check_command_in_paths(cmd, paths);
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (path);
}

void	execute(char *argv, char **envp)
{
	char	**cmd;
	char	*path;
	int		i;

	i = -1;
	path = removecharta(argv, "'");
	cmd = ft_split(path, ' ');
	free(path);
	if (ft_strchr(cmd[0], '/'))
	{
		if (access(cmd[0], F_OK | X_OK) == -1)
			perror("error");
		execve(cmd[0], cmd, envp);
	}
	path = find_path(cmd[0], envp);
	if (!path)
	{
		while (cmd[++i])
			free(cmd[i]);
		free(cmd);
		write(2, "error: command not found\n", 25);
		exit(127);
	}
	if (execve(path, cmd, envp) == -1)
		error();
}
