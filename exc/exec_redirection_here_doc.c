/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection_here_doc.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:26:37 by sodahani          #+#    #+#             */
/*   Updated: 2025/04/27 22:41:09 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_next_line(char **line)
{
	char	*buffer;
	char	c;
	int		i;
	int		r;

	buffer = ft_malloc(10000, FT_ALLOC);
	if (!buffer)
		return (-1);
	i = 0;
	r = read(0, &c, 1);
	while (r > 0)
	{
		if (c == '\n')
			break ;
		buffer[i++] = c;
		r = read(0, &c, 1);
	}
	buffer[i] = '\0';
	*line = buffer;
	return (r);
}

int	handle_child_process(t_ast *node, int fd[2])
{
	char	*line;

	close(fd[0]);
	while (1)
	{
		write(1, "> ", 2);
		if (get_next_line(&line) <= 0)
			break ;
		if (ft_strncmp(line, node->r->cmd[0], ft_strlen(node->r->cmd[0])) == 0
			&& ft_strlen(line) == ft_strlen(node->r->cmd[0]))
			break ;
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
	}
	close(fd[1]);
	ft_malloc(0, FT_CLEAR);
	exit(0);
}

int	typ_redhere_fun(t_ast *node, char ***envp, t_export_store *store)
{
	pid_t	pid;
	int		status;
	int		fd[2];
	int		original_stdin;
	int		ret;

	if (pipe(fd) == -1)
		return (perror("pipe"), 1);
	pid = fork();
	reset_signals();
	setup_execution_signals();
	if (pid == -1)
		return (perror("fork"), 1);
	if (pid == 0)
		handle_child_process(node, fd);
	original_stdin = dup(STDIN_FILENO);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	waitpid(pid, &status, 0);
	ret = execute_ast(node->l, envp, store);
	dup2(original_stdin, STDIN_FILENO);
	close(original_stdin);
	return (ret);
}
