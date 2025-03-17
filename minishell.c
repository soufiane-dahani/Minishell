/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:26:37 by sodahani          #+#    #+#             */
/*   Updated: 2025/03/17 17:47:59 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

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
                execute_unset(&envp, node->cmd[1]);
            } else {
                print_error("unset: expected argument\n");
            }
        }
        
        else
        {
            execute_simple_command(node->cmd, envp);
        }
    }
    else if (node->type == PIPE)
    {
        // Execute a pipe command (e.g., "ls | grep txt")
        execute_pipe(node, envp);
    }
    // else if (node->type == REDIRECT_OUT || node->type == REDIRECT_IN || node->type == APPEND_OUT) {
    //     // Handle redirections (e.g., "ls > output.txt")
    //     execute_redirection(node, envp);
    // }
    // else if (node->type == AND || node->type == OR) {
    //     execute_logical_operators(node, envp);
    // }
    // else {
    //     print_error("Unknown AST node type\n");
    // }
}



int main(int argc, char **argv, char **envp)
{
    // Create AST for: ls | grep .c | wc -l
    // Note: The proper way to structure it depends on how your parser builds the AST
    
    // Method 1: Right-linked list (if your parser works this way)
    t_ast_node cmd1, cmd2, cmd3, pipe1, pipe2;
    
    // Command 1: ls
    char *cmd_ls[] = {"ls", NULL};
    cmd1.type = SIMPLE_CMD;
    cmd1.cmd = cmd_ls;
    cmd1.left = NULL;
    cmd1.right = NULL;
    
    // Command 2: grep .c
    char *cmd_grep[] = {"grep", "j", NULL};
    cmd2.type = SIMPLE_CMD;
    cmd2.cmd = cmd_grep;
    cmd2.left = NULL;
    cmd2.right = NULL;
    
    // Command 3: wc -l
    char *cmd_wc[] = {"wc", "-l", NULL};
    cmd3.type = SIMPLE_CMD;
    cmd3.cmd = cmd_wc;
    cmd3.left = NULL;
    cmd3.right = NULL;
    
    // This is the structure your execute_pipe expects:
    //     PIPE (pipe1)
    //    /    \
    //  cmd1    PIPE (pipe2)
    //         /    \
    //      cmd2     cmd3
    
    pipe2.type = PIPE;
    pipe2.left = &cmd2;
    pipe2.right = &cmd3;
    
    pipe1.type = PIPE;
    pipe1.left = &cmd1;
    pipe1.right = &pipe2;
    
    // Print debugging info about the AST structure
    
    // Execute the pipeline
    execute_pipe(&pipe1, envp);
    
    return 0;
}

