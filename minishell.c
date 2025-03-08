/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:26:37 by sodahani          #+#    #+#             */
/*   Updated: 2025/03/08 14:11:17 by sodahani         ###   ########.fr       */
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
    // Simulate a simple command (normally, this would come from the parser)
    t_ast_node test_cmd;
    char *cmd[] = {"ls", "-l", NULL}; // Replace with any command to test

    // Fill the AST node manually
    test_cmd.type = SIMPLE_CMD;
    test_cmd.cmd = cmd;
    test_cmd.file = NULL;
    test_cmd.left = NULL;
    test_cmd.right = NULL;

    // Execute the test command
    execute_ast(&test_cmd, envp);

    return 0;
}
