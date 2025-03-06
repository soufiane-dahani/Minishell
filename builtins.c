/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:26:37 by sodahani          #+#    #+#             */
/*   Updated: 2025/03/06 10:32:41 by sodahani         ###   ########.fr       */
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

void execute_exit()
{
    exit(0);
}
void execute_unset(char ***envp, char *var_name)
{
    int i = 0;
    int found = 0;
    while ((*envp)[i] != NULL) {
        if (ft_strncmp((*envp)[i], var_name, ft_strlen(var_name)) == 0 && (*envp)[i][ft_strlen(var_name)] == '=') {

            free((*envp)[i]);
            found = 1;
            break;
        }
        i++;
    }

    if (found) {
        while ((*envp)[i] != NULL) {
            (*envp)[i] = (*envp)[i + 1];
            i++;
        }
        (*envp)[i] = NULL;
    } else {
        print_error("unset: variable not found\n");
    }
}

void execute_export(char **envp)
{
    int i;
    i = 0;
    while (envp[i])
    {
        printf("%s\n", envp[i]);
        i++;
    }
    
}

