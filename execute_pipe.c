/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:26:37 by sodahani          #+#    #+#             */
/*   Updated: 2025/03/08 14:17:22 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void execute_pipe(t_ast_node *node, char **envp)
{
    t_process process;
    char *path;

    if (pipe(process.pipe_fd) == -1)
    {
        perror("pipe failed");
        exit(EXIT_FAILURE);
    }

    // First child process (left command)
    process.pid = fork();
    if (process.pid == -1)
    {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }
    if (process.pid == 0)
    {
        close(process.pipe_fd[0]);
        dup2(process.pipe_fd[1], STDOUT_FILENO);
        close(process.pipe_fd[1]);

        if (ft_strchr(node->left->cmd[0], '/'))
            path = node->left->cmd[0];
        else
            path = find_path(node->left->cmd[0], envp);

        if (!path)
        {
            write(2, "error: command not found\n", 25);
            exit(127);
        }

        execve(path, node->left->cmd, envp);
        perror("execve failed");
        exit(EXIT_FAILURE);
    }

    // Second child process (right command)
    process.pid = fork();
    if (process.pid == -1)
    {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }
    if (process.pid == 0)
    {
        close(process.pipe_fd[1]);
        dup2(process.pipe_fd[0], STDIN_FILENO);
        close(process.pipe_fd[0]);

        if (ft_strchr(node->right->cmd[0], '/'))
            path = node->right->cmd[0];
        else
            path = find_path(node->right->cmd[0], envp);

        if (!path)
        {
            write(2, "error: command not found\n", 25);
            exit(127);
        }

        execve(path, node->right->cmd, envp);
        perror("execve failed");
        exit(EXIT_FAILURE);
    }

    // Parent Process: Close pipe ends and wait for both children
    close(process.pipe_fd[0]);
    close(process.pipe_fd[1]);

    waitpid(-1, NULL, 0);
    waitpid(-1, NULL, 0);
}


void	error(void)
{
	perror("Error");
	exit(126);
}
