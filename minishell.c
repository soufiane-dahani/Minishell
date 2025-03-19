/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:26:37 by sodahani          #+#    #+#             */
/*   Updated: 2025/03/19 18:15:04 by sodahani         ###   ########.fr       */
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
    else if (ft_strncmp(node->cmd[0], "export", 6) == 0)
    {
        if (node->cmd[1] == NULL) {
            print_export(envp);
        } else {
            execute_export(&envp, node->cmd);  // Pass pointer to envp
        }
    }
    else if (ft_strncmp(node->cmd[0], "env", 3) == 0)
        execute_env(envp);  // Pass envp directly
    else if (ft_strncmp(node->cmd[0], "unset", 5) == 0) {
        if (node->cmd[1] != NULL) {
            execute_unset(&envp, node->cmd[1]);  // Pass pointer to envp
        } else {
            print_error("unset: expected argument\n");
        }
    }
    else
    {
        execute_simple_command(node->cmd, envp);  // Pass envp directly
    }
}
else if (node->type == PIPE)
{
    execute_pipe(node, envp);  // Pass envp directly
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
    (void)argc;
    (void)argv;

    // Create a copy of envp to modify
    char **my_envp;
    int i = 0;
    while (envp[i])
        i++;
    my_envp = malloc((i + 1) * sizeof(char *));
    if (!my_envp)
        return (perror("malloc failed"), 1);
    for (i = 0; envp[i]; i++)
        my_envp[i] = strdup(envp[i]);
    my_envp[i] = NULL;

    // Test 1: `export NEW_VAR=value`
    t_ast_node export_cmd;
    char *cmd_export[] = {"export", "NEW_VAR=HelloWorld", NULL};
    export_cmd.type = SIMPLE_CMD;
    export_cmd.cmd = cmd_export;
    export_cmd.left = NULL;
    export_cmd.right = NULL;

    printf("\n--- Executing: export NEW_VAR=HelloWorld ---\n");
    execute_ast(&export_cmd, my_envp);  // Pass my_envp (char **)

    // Test 2: `env` (should include NEW_VAR)
    t_ast_node env_cmd;
    char *cmd_env[] = {"env", NULL};
    env_cmd.type = SIMPLE_CMD;
    env_cmd.cmd = cmd_env;
    env_cmd.left = NULL;
    env_cmd.right = NULL;

    printf("\n--- Executing: env ---\n");
    execute_ast(&env_cmd, my_envp);  // Pass my_envp (char **)

    // Test 3: `export` without arguments (should list environment variables)
    t_ast_node export_no_args_cmd;
    char *cmd_export_no_args[] = {"export", NULL};
    export_no_args_cmd.type = SIMPLE_CMD;
    export_no_args_cmd.cmd = cmd_export_no_args;
    export_no_args_cmd.left = NULL;
    export_no_args_cmd.right = NULL;

    printf("\n--- Executing: export (without arguments) ---\n");
    execute_ast(&export_no_args_cmd, my_envp);  // Pass my_envp (char **)

    // Free allocated memory
    for (i = 0; my_envp[i]; i++)
        free(my_envp[i]);
    free(my_envp);

    return 0;
}
