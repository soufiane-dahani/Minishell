/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:26:37 by sodahani          #+#    #+#             */
/*   Updated: 2025/03/17 17:46:42 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void execute_pipe(t_ast_node *node, char **envp)
{
    // Add debug output
    //fprintf(stderr, "DEBUG: Starting execute_pipe\n");
    
    // Count commands and create an array of commands
    int cmd_count = 0;
    t_ast_node **commands = NULL;
    
    // First, flatten the AST to get all commands in order
    t_ast_node *current = node;
    while (current) {
        if (current->type == PIPE) {
            // Debug output
            //fprintf(stderr, "DEBUG: Found PIPE node\n");
            
            // Check if left node exists and is a command
            if (current->left && current->left->type == SIMPLE_CMD) {
                //fprintf(stderr, "DEBUG: Adding command: %s\n", current->left->cmd[0]);
                
                // Allocate more space for commands
                t_ast_node **temp = realloc(commands, (cmd_count + 1) * sizeof(t_ast_node *));
                if (!temp) {
                    perror("realloc failed");
                    free(commands);
                    exit(EXIT_FAILURE);
                }
                commands = temp;
                commands[cmd_count++] = current->left;
            }
            
            // Move to right child (next pipe or command)
            if (current->right) {
                if (current->right->type == SIMPLE_CMD) {
                    // Last command
                    //fprintf(stderr, "DEBUG: Adding last command: %s\n", current->right->cmd[0]);
                    
                    t_ast_node **temp = realloc(commands, (cmd_count + 1) * sizeof(t_ast_node *));
                    if (!temp) {
                        perror("realloc failed");
                        free(commands);
                        exit(EXIT_FAILURE);
                    }
                    commands = temp;
                    commands[cmd_count++] = current->right;
                    break;
                }
                current = current->right;
            } else {
                //fprintf(stderr, "DEBUG: No right node found, breaking\n");
                break;
            }
        } else if (current->type == SIMPLE_CMD) {
            // Single command, no pipes
            //fprintf(stderr, "DEBUG: Single command: %s\n", current->cmd[0]);
            
            t_ast_node **temp = realloc(commands, sizeof(t_ast_node *));
            if (!temp) {
                perror("realloc failed");
                free(commands);
                exit(EXIT_FAILURE);
            }
            commands = temp;
            commands[cmd_count++] = current;
            break;
        } else {
            //fprintf(stderr, "DEBUG: Unknown node type: %d\n", current->type);
            break;
        }
    }
    
    //fprintf(stderr, "DEBUG: Found %d commands\n", cmd_count);
    
    // Number of pipes is one less than number of commands
    int num_pipes = cmd_count - 1;
    //fprintf(stderr, "DEBUG: Creating %d pipes\n", num_pipes);
    
    // Check if we have a valid number of commands
    if (cmd_count < 2) {
        //fprintf(stderr, "DEBUG: Not enough commands for a pipe\n");
        free(commands);
        return;
    }
    
    // Create pipes array
    int **pipes = malloc(num_pipes * sizeof(int *));
    if (!pipes) {
        perror("malloc failed");
        free(commands);
        exit(EXIT_FAILURE);
    }
    
    for (int i = 0; i < num_pipes; i++) {
        pipes[i] = malloc(2 * sizeof(int));
        if (!pipes[i]) {
            perror("malloc failed");
            for (int j = 0; j < i; j++) {
                free(pipes[j]);
            }
            free(pipes);
            free(commands);
            exit(EXIT_FAILURE);
        }
        
        if (pipe(pipes[i]) == -1) {
            perror("pipe failed");
            for (int j = 0; j <= i; j++) {
                free(pipes[j]);
            }
            free(pipes);
            free(commands);
            exit(EXIT_FAILURE);
        }
        //fprintf(stderr, "DEBUG: Created pipe %d: read=%d, write=%d\n", i, pipes[i][0], pipes[i][1]);
    }
    
    pid_t *pids = malloc(cmd_count * sizeof(pid_t));
    if (!pids) {
        perror("malloc failed");
        for (int i = 0; i < num_pipes; i++) {
            free(pipes[i]);
        }
        free(pipes);
        free(commands);
        exit(EXIT_FAILURE);
    }
    
    // Execute all commands
    for (int i = 0; i < cmd_count; i++) {
        //fprintf(stderr, "DEBUG: Forking for command %d: %s\n", i, commands[i]->cmd[0]);
        
        pids[i] = fork();
        if (pids[i] == -1) {
            perror("fork failed");
            for (int j = 0; j < num_pipes; j++) {
                free(pipes[j]);
            }
            free(pipes);
            free(commands);
            free(pids);
            exit(EXIT_FAILURE);
        }
        
        if (pids[i] == 0) {
            // Child process
            //fprintf(stderr, "DEBUG: Child %d started\n", i);
            
            // Redirect stdin from previous pipe (if not first command)
            if (i > 0) {
                //fprintf(stderr, "DEBUG: Child %d redirecting stdin from pipe %d\n", i, i - 1);
                if (dup2(pipes[i - 1][0], STDIN_FILENO) == -1) {
                    perror("dup2 failed for stdin");
                    exit(EXIT_FAILURE);
                }
            }
            
            if (i < num_pipes) {
                if (dup2(pipes[i][1], STDOUT_FILENO) == -1) {
                    perror("dup2 failed for stdout");
                    exit(EXIT_FAILURE);
                }
            }
            
            for (int j = 0; j < num_pipes; j++) {
                close(pipes[j][0]);
                close(pipes[j][1]);
            }
            char *path;
            if (ft_strchr(commands[i]->cmd[0], '/'))
                path = commands[i]->cmd[0];
            else
                path = find_path(commands[i]->cmd[0], envp);
                
            if (!path) {
                write(2, "error: command not found\n", 25);
                for (int j = 0; j < num_pipes; j++) {
                    free(pipes[j]);
                }
                free(pipes);
                free(commands);
                free(pids);
                exit(127);
            }
            execve(path, commands[i]->cmd, envp);
            perror("execve failed");
            for (int j = 0; j < num_pipes; j++) {
                free(pipes[j]);
            }
            free(pipes);
            free(commands);
            free(pids);
            exit(EXIT_FAILURE);
        }
    }
    for (int j = 0; j < num_pipes; j++) {
        close(pipes[j][0]);
        close(pipes[j][1]);
    }
    
    for (int j = 0; j < cmd_count; j++) {
        int status;
        waitpid(pids[j], &status, 0);
    }
    
    for (int i = 0; i < num_pipes; i++) {
        free(pipes[i]);
    }
    free(pipes);
    free(commands);
    free(pids);
}



void	error(void)
{
	perror("Error");
	exit(126);
}
