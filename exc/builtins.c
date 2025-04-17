/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:26:37 by sodahani          #+#    #+#             */
/*   Updated: 2025/04/17 19:12:57 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

int execute_cd(char *path)
{
    if (path == NULL) {
        print_error("cd: expected argument\n");
        return 1;
    }
    if (chdir(path) == -1) {
        print_error("No such file or directory ");
        print_error(path);
        print_error("\n");
        return 1;
    }
    return 0;
}

int execute_pwd(void) {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
        return 0;
    } else {
        perror("pwd");
        return 1;
    }
}

int execute_exit(void)
{
    exit(0); // this never returns
    return 0;
}

int execute_unset(char ***envp, char *var_name)
{
    int i = 0;
    int found = 0;

    while ((*envp)[i] != NULL) {
        if (ft_strncmp((*envp)[i], var_name, ft_strlen(var_name)) == 0 &&
            (*envp)[i][ft_strlen(var_name)] == '=') {
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
        return 0;
    } else {
        print_error("unset: variable not found\n");
        return 1;
    }
}

int is_valid_identifier(const char *var)
{
    int i = 1;
    if (!var || (!ft_isalpha(var[0]) && var[0] != '_'))
        return 0;
    while (var[i] && var[i] != '=')
    {
        if (!ft_isalnum(var[i]) && var[i] != '_')
            return 0;
        i++;
    }
    return 1;
}

int add_to_env(char ***envp, const char *new_var)
{
    char *key;
    char *equal_sign;
    char **new_envp;
    int i = 0;
    int j = 0;

    if (!new_var || !ft_strchr(new_var, '=')) {
        print_error("export: ");
        write(2, new_var, ft_strlen(new_var));
        print_error(": not a valid identifier\n");
        return 1;
    }

    equal_sign = ft_strchr(new_var, '=');
    key = ft_substr(new_var, 0, equal_sign - new_var);

    if (!is_valid_identifier(key)) {
        print_error("export: ");
        write(2, new_var, ft_strlen(new_var));
        print_error(": not a valid identifier\n");
        free(key);
        return 1;
    }

    while ((*envp)[i]) {
        if (ft_strncmp((*envp)[i], key, ft_strlen(key)) == 0 &&
            (*envp)[i][ft_strlen(key)] == '=') {
            free((*envp)[i]);
            (*envp)[i] = ft_strdup(new_var);
            free(key);
            return 0;
        }
        i++;
    }

    new_envp = malloc((i + 2) * sizeof(char *));
    if (!new_envp) {
        perror("malloc failed");
        free(key);
        return 1;
    }

    while (j < i) {
        new_envp[j] = (*envp)[j];
        j++;
    }
    new_envp[i] = ft_strdup(new_var);
    new_envp[i + 1] = NULL;
    free(*envp);
    *envp = new_envp;
    free(key);
    return 0;
}

int execute_export(char ***envp, char **cmd)
{
    int i = 1;
    int status = 0;

    while (cmd[i]) {
        if (ft_strchr(cmd[i], '=')) {
            if (add_to_env(envp, cmd[i]) != 0)
                status = 1;
        } else {
            print_error("export: `");
            write(2, cmd[i], ft_strlen(cmd[i]));
            print_error("': not a valid identifier\n");
            status = 1;
        }
        i++;
    }
    return status;
}

int execute_env(char **envp)
{
    int i = 0;
    while (envp[i]) {
        printf("%s\n", envp[i]);
        i++;
    }
    return 0;
}

int print_export(char **envp)
{
    int i = 0;
    while (envp[i]) {
        printf("declare -x %s\n", envp[i]);
        i++;
    }
    return 0;
}
