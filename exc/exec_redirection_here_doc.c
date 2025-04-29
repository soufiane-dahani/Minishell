/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection_here_doc.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:26:37 by sodahani          #+#    #+#             */
/*   Updated: 2025/04/29 15:25:13 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	more_expand(char **new, int *i, char *s, int *a)
{
	int		j;
	char	*store;
	char	*env;

	j = 0;
	store = ft_malloc((ft_strlen(s) * sizeof(char)) + 1, FT_ALLOC);
	(*i)++;
	while (s[(*i)] && ft_isalnum(s[(*i)]))
		store [j++] = s[(*i)++];
	store[j] = '\0';
	env = getenv(store);
	if (env)
	{
		j = 0;
		while (env[j])
			(*new)[(*a)++] = env[j++];
	}
}

char	*exp_for_herdoc(char *s)
{
	int		i;
	int		a;
	char	*env;
	char	*new;

	i = 0;
	env = ft_malloc(ft_strlen(s) + 1, FT_ALLOC);
	a = calculate_s(s, env);
	new = ft_malloc(a * sizeof(char) + 1, FT_ALLOC);
	a = 0;
	while (s[i])
	{
		if (s[i] == '$')
			more_expand(&new, &i, s, &a);
		else
			new[a++] = s[i++];
	}
	new[a] = '\0';
	return (new);
}

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
		if (node->r->type != TYP_SQOUTE && node->r->type != TYP_DQUOTE)
			line = exp_for_herdoc(line);
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
	t_ast	*cur;
	t_ast	*par;
	int		ret;

	ret = 0;
	cur = node;
	original_stdin = dup(STDIN_FILENO);
	if (original_stdin == -1)
		return (perror("dup"), 1);
	while (cur->l && cur->l->type == TYP_REDHERE)
		cur = cur->l;
	while (cur && cur->type == TYP_REDHERE)
	{
		if (pipe(fd) == -1)
			return (perror("pipe"), 1);
		pid = fork();
		reset_signals();
		setup_execution_signals();
		if (pid == -1)
			return (perror("fork"), 1);
		if (pid == 0)
			handle_child_process(cur, fd);
		int temp_stdin = dup(STDIN_FILENO);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		waitpid(pid, &status, 0);
		if (cur == node)
			break ;
		par = node;
		while (par->l != cur)
			par = par->l;
		cur = par;
		dup2(temp_stdin, STDIN_FILENO);
		close(temp_stdin);
	}
	while (node->l && node->l->type == TYP_REDHERE)
		node = node->l;
	if (node->l && node->l->type != TYP_REDHERE)
		ret = execute_ast(node->l, envp, store);
	dup2(original_stdin, STDIN_FILENO);
	close(original_stdin);
	return (ret);
}
