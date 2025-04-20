/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:26:37 by sodahani          #+#    #+#             */
/*   Updated: 2025/04/20 19:44:23 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	open_file(char *filename, int mode)
{
	int	fd;

	if (mode == 0) // >> append
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (mode == 1) // > truncate
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (mode == 2) // < read
		fd = open(filename, O_RDONLY);
	else
		return (-1);
	return (fd);
}


int	typ_redout_fun(t_ast *node, char ***envp)
{
	pid_t	pid;
	int		status;
	int		out_fd;

	pid = fork();
	if (pid == -1)
		return (perror("fork"), 1);

	if (pid == 0)
	{
		out_fd = open_file(node->r->cmd[0], 1);
		if (out_fd == -1)
		{
			perror("open");
			exit(1);
		}
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);

		execute_ast(node->l, envp);
		exit(1);
	}
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}
int	typ_redin_fun(t_ast *node, char ***envp)
{
	pid_t	pid;
	int		status;
	int		in_fd;

	pid = fork();
	if (pid == -1)
		return (perror("fork"), 1);

	if (pid == 0)
	{
		in_fd = open_file(node->r->cmd[0], 2);
		if (in_fd == -1)
		{
			perror("open");
			exit(1);
		}
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);

		execute_ast(node->l, envp);
		exit(1);
	}
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}
int	typ_redapp_fun(t_ast *node, char ***envp)
{
	pid_t	pid;
	int		status;
	int		out_fd;

	pid = fork();
	if (pid == -1)
		return (perror("fork"), 1);

	if (pid == 0)
	{
		out_fd = open_file(node->r->cmd[0], 0);
		if (out_fd == -1)
		{
			perror("open");
			exit(1);
		}
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);

		execute_ast(node->l, envp);
		exit(1);
	}
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}

int	get_next_line(char **line)
{
	char	*buffer;
	char	c;
	int		i;
	int		r;

	buffer = malloc(10000);
	if (!buffer)
		return (-1);

	i = 0;
	while ((r = read(0, &c, 1)) > 0)
	{
		if (c == '\n')
			break;
		buffer[i++] = c;
	}
	buffer[i] = '\0';
	*line = buffer;
	return (r);
}



int typ_redhere_fun(t_ast *node, char ***envp)
{
	pid_t	pid;
	int		status;
	int		fd[2];
	int		original_stdin;
	char	*line;

	if (pipe(fd) == -1)
		return (perror("pipe"), 1);

	pid = fork();
	if (pid == -1)
		return (perror("fork"), 1);

	if (pid == 0)
	{
		close(fd[0]);
		while (1)
		{
			write(1, "> ", 2);
			if (get_next_line(&line) <= 0)
				break;

			if (ft_strncmp(line, node->r->cmd[0], ft_strlen(node->r->cmd[0])) == 0
				&& ft_strlen(line) == ft_strlen(node->r->cmd[0]))
			{
				free(line);
				break;
			}
			write(fd[1], line, ft_strlen(line));
			write(fd[1], "\n", 1);
			free(line);
		}
		close(fd[1]);
		exit(0);
	}

	// 🛠️ Save original stdin
	original_stdin = dup(STDIN_FILENO);

	close(fd[1]);
	dup2(fd[0], STDIN_FILENO); // heredoc input becomes stdin
	close(fd[0]);

	waitpid(pid, &status, 0);

	int ret = execute_ast(node->l, envp);

	// 🔁 Restore original stdin
	dup2(1, STDIN_FILENO);
	close(original_stdin);

	return ret;
}



int	exec_redirection(t_ast *node, char ***envp)
{
	if (!node || !(node->type == TYP_REDOUT || node->type == TYP_REDAPP ||
		node->type == TYP_REDIN || node->type == TYP_REDHERE))
		return (1);

	if (node->type == TYP_REDOUT)
		return typ_redout_fun(node, envp);
	else if (node->type == TYP_REDIN)
		return typ_redin_fun(node, envp);
	else if (node->type == TYP_REDAPP)
		return typ_redapp_fun(node, envp);
	else if (node->type == TYP_REDHERE)
		return typ_redhere_fun(node, envp);	
	return (1);
}

