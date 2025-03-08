/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:26:37 by sodahani          #+#    #+#             */
/*   Updated: 2025/03/08 16:08:18 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void execute_pipe(t_ast_node *node, char **envp)
{
    int num_pipes = 0;
    t_ast_node *tmp = node;

    // Count number of pipes (each pipe separates two commands)
    while (tmp)
    {
        if (tmp->type == PIPE)
            num_pipes++;
        tmp = tmp->right;
    }

    int pipes[num_pipes][2];
    int i = 0;
    t_ast_node *current = node;
    pid_t pid;

    while (i < num_pipes)
    {
        if (pipe(pipes[i]) == -1)
        {
            perror("pipe failed");
            exit(EXIT_FAILURE);
        }
        i++;
    }

    i = 0;
    while (current)
    {
        pid = fork();
        if (pid == -1)
        {
            perror("fork failed");
            exit(EXIT_FAILURE);
        }

        if (pid == 0)
        {
            // Redirect stdin from previous pipe (if not first command)
            if (i > 0)
                dup2(pipes[i - 1][0], STDIN_FILENO);

            // Redirect stdout to next pipe (if not last command)
            if (i < num_pipes)
                dup2(pipes[i][1], STDOUT_FILENO);

            // Close all pipes in child process
            int j = 0;
            while (j < num_pipes)
            {
                close(pipes[j][0]);
                close(pipes[j][1]);
                j++;
            }
            char *path;
            if (ft_strchr(current->cmd[0], '/'))
                path = current->cmd[0];
            else
                path = find_path(current->cmd[0], envp);

            if (!path)
            {
                write(2, "error: command not found\n", 25);
                exit(127);
            }

            execve(path, current->cmd, envp);
            perror("execve failed");
            exit(EXIT_FAILURE);
        }

        // Move to next command
        current = current->right;
        i++;
    }
    int j = 0;
    while (j < num_pipes)
    {
        close(pipes[j][0]);
        close(pipes[j][1]);
        j++;
    }
    j = 0;
    while (j <= num_pipes)
    {
        waitpid(-1, NULL, 0);
        j++;
    }
}



void	error(void)
{
	perror("Error");
	exit(126);
}
