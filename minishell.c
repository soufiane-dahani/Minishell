/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:26:37 by sodahani          #+#    #+#             */
/*   Updated: 2025/02/23 12:32:03 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void execute_cd(char *path)
{
    if (path == NULL) {
        print_error("cd: expected argument\n");
        return;
    }
    if (chdir(path) == -1) {
        print_error("No such file or directory ");
        print_error(path);
        print_error("\n");
    }
}

void execute_pwd() {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
    } else{
        perror("pwd");
    }
}


void execute_ast(t_ast_node *node, char **envp)
{
    if (!node)
        return;

    if (node->type == SIMPLE_CMD) {
       if (ft_strncmp(node->cmd[0], "cd", 2) == 0) {
            execute_cd(node->cmd[1]);
        }
        else if ((ft_strncmp(node->cmd[0], "pwd", 3) == 0))
        {
            execute_pwd();
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