/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:26:37 by sodahani          #+#    #+#             */
/*   Updated: 2025/04/20 17:03:37 by sodahani         ###   ########.fr       */
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
	int		i;
	int		r;
	char	c;

	i = 0;
	buffer = ft_malloc(10000, FT_ALLOC);
	if (!buffer)
		return (-1);
	r = read(0, &c, 1);
	while (r && c != '\n' && c != '\0')
	{
		if (c != '\n' && c != '\0')
			buffer[i] = c;
		i++;
		r = read(0, &c, 1);
	}
	buffer[i] = '\0';
	*line = buffer;
	return (r);
}

void	write_to_pipe(int fd[2], char *limiter)
{
	char	*line;

	close(fd[0]);
	while (get_next_line(&line))
	{
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0
			&& ft_strlen(line) == ft_strlen(limiter))
		{
			free(line);
			exit(EXIT_SUCCESS);
		}
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
}


int	typ_redhere_fun(t_ast *node, char ***envp)
{
	pid_t	pid;
	int		fd[2];
	int		status;
	
	if (pipe(fd) == -1)
		perror("pipe");
	pid = fork();
	if (pid == 0)
	{
		write_to_pipe(fd, node->r->cmd[0]);
		execute_ast(node->l, envp);
		exit(1);
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
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

