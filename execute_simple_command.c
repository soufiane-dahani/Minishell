/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:26:37 by sodahani          #+#    #+#             */
/*   Updated: 2025/03/19 17:53:06 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

char	*check_command_in_paths(char *cmd, char **paths)
{
	char	*path;
	char	*part_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK | X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
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
	if (!paths)
		return (NULL);
	path = check_command_in_paths(cmd, paths);

	return (path);
}

void execute_simple_command(char **cmd, char **envp)
{
    char	*path;
    pid_t	pid;

    pid = fork();
    if (pid == -1)
    {
        perror("fork failed");
        return;
    }
    if (pid == 0)
    {
        if (ft_strchr(cmd[0], '/'))
        {
            if (access(cmd[0], F_OK | X_OK) == -1)
            {
                perror("error");
                exit(EXIT_FAILURE);
            }
            execve(cmd[0], cmd, envp);
        }
        path = find_path(cmd[0], envp);
        if (!path)
        {
            write(2, "error: command not found\n", 25);
            exit(127);
        }
        if (execve(path, cmd, envp) == -1)
        {
            free(path);
            perror("execve failed");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        waitpid(pid, NULL, 0);
    }
}
