/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:26:37 by sodahani          #+#    #+#             */
/*   Updated: 2025/03/06 15:35:39 by sodahani         ###   ########.fr       */
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
	i = 0;
	while (paths[i])
		free(paths[i]);
	free(paths);
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


void execute_ast(t_ast_node *node, char **envp)
{
    if (!node)
        return;

    if (node->type == SIMPLE_CMD) {
       if (ft_strncmp(node->cmd[0], "cd", 2) == 0)
            execute_cd(node->cmd[1]);
        else if ((ft_strncmp(node->cmd[0], "pwd", 3) == 0))
            execute_pwd();

        else if ((ft_strncmp(node->cmd[0], "exit", 4) == 0))
            execute_exit();
        else if ((ft_strncmp(node->cmd[0], "export", 6) == 0) || (ft_strncmp(node->cmd[0], "env", 3) == 0))
            execute_export(envp);
        else if (ft_strncmp(node->cmd[0], "unset", 5) == 0) {
            if (node->cmd[1] != NULL) {
                execute_unset(envp, node->cmd[1]);
            } else {
                print_error("unset: expected argument\n");
            }
        }
        
        else
        {
            execute_simple_command(node->cmd, envp);
        }
    }
    else if (node->type == PIPE) {
        // Execute a pipe command (e.g., "ls | grep txt")
        execute_pipe(node, envp);
    }
    else if (node->type == REDIRECT_OUT || node->type == REDIRECT_IN || node->type == APPEND_OUT) {
        // Handle redirections (e.g., "ls > output.txt")
        execute_redirection(node, envp);
    }
    else if (node->type == AND || node->type == OR) {
        execute_logical_operators(node, envp);
    }
    else {
        print_error("Unknown AST node type\n");
    }
}



int	main(int argc, char **argv, char **envp)
{
    execute_pwd();
}