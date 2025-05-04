/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:26:37 by sodahani          #+#    #+#             */
/*   Updated: 2025/05/04 15:56:54 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void close_fd(int fd)
{
    if (fd >= 3)
        close(fd);
}

int get_in_out_file(t_token *redir, int *in_file, int *out_file)
{
    int fd;

    while (redir)
    {
		redir->next->value = exp_for_herdoc(redir->next->value);
		redir->next->value = exp_for_herdoc(redir->next->value);
        fd = open_file(redir->next->value, redir->type);
        if (fd == -1)
        {
            perror("error");
            return (1);
        }
        if (redir->type == TYP_REDIN)
        {
            close_fd(*in_file);
            *in_file = fd;
        }
        else
        {
            close_fd(*out_file);
            *out_file = fd;
        }
        redir = redir->next->next;
    }
    return (0);
}

int get_redirections(t_ast *cmd, int *in_file, int *out_file)
{
    t_token *redir;

    *in_file = -1;
    *out_file = -1;
    if (!cmd->redir)
        return (0);
    redir = cmd->redir;
    if (get_in_out_file(redir, in_file, out_file))
        return (1);
    if (*in_file != -1 && dup2(*in_file, STDIN_FILENO) == -1)
    {
        perror("dup2");
        ft_malloc(0, FT_CLEAR);
        exit(1);
    }
    if (*out_file != -1 && dup2(*out_file, STDOUT_FILENO) == -1)
    {
        perror("dup2");
        ft_malloc(0, FT_CLEAR);
        exit(1);
    }
    return (0);
}

int apply_redirections(t_ast *node, char ***envp, t_export_store *store)
{
    int in_fd;
    int out_fd;
    int status;
    pid_t pid;

    pid = fork();
    if (pid == -1)
        return (perror("fork"), -1);

    if (pid == 0)
    {
        reset_signals();
        if (get_redirections(node, &in_fd, &out_fd))
        {
            ft_malloc(0, FT_CLEAR);
            exit(1);
        }

        int exit_status = 0;
        if (is_builtin(node->cmd))
            exit_status = exec_builtin(node, envp, store);
        else
            exit_status = exec_external(node, *envp);
        close_fd(in_fd);
        close_fd(out_fd);
        ft_malloc(0, FT_CLEAR);
        exit(exit_status);
    }
    else
    {
        waitpid(pid, &status, 0);
        return WEXITSTATUS(status);
    }
}
