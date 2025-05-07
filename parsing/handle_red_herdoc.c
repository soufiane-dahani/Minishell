/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_red_herdoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:21:20 by yaait-am          #+#    #+#             */
/*   Updated: 2025/05/07 14:27:06 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int get_next_line(char **line)
{
	char *buffer;
	char c;
	int i;
	int r;

	buffer = ft_malloc(10000, FT_ALLOC);
	if (!buffer)
		return (-1);

	i = 0;
	r = read(0, &c, 1);
	while (r > 0)
	{
		if (c == '\n')
			break;
		buffer[i++] = c;
		r = read(0, &c, 1);
	}
	buffer[i] = '\0';
	*line = buffer;
	return (r);
}

static char *read_the_herdoc(char *delimiter)
{
	char *buffer;
	char *total;

	total = ft_strdup("");
	delimiter = skip_quote(delimiter);
	while (1)
	{
		write(1, "> ", 2);
		int result = get_next_line(&buffer);
		if (result < 0)
			return NULL;
		if (result == 0 || ft_strcmp(buffer, delimiter) == 0)
			break;
		total = ft_strjoin(total, buffer);
		total = ft_strjoin(total, "\n");
	}
	return total;
}

static void change_herdoc_to_red(t_token **new, t_token **tmp, int a)
{
	char *content;
	char *delimiter;
	int fd;
	static char *name;

	delimiter = NULL;
	if ((*tmp)->next)
		delimiter = (*tmp)->next->value;
	if (!a)
	{
		name = ft_strjoin("/tmp/", random_str());
		add_token(new, "<", TYP_REDIN, 0);
		add_token(new, name, TYP_WORD, 0);
	}
	content = read_the_herdoc(delimiter);
	if (content == NULL)
	{
		*new = NULL;
		return ;
	}
	if ((*tmp)->next && (*tmp)->next->type != TYP_SQOUTE && (*tmp)->next->type != TYP_DQUOTE)
		content = exp_for_herdoc(content);
	fd = open(name, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	write(fd, content, ft_strlen(content));
	close(fd);
	if ((*tmp)->next)
		*tmp = (*tmp)->next;
}

int	calcul_herdoc(t_token *tk)
{
	t_token	*tmp;
	int		a;
	tmp = tk;
	a = 0;
	while (tmp)
	{
		if (tmp->type == TYP_REDHERE)
			a++;
		if (tmp->type == TYP_PIPE)
			a = 0;
		if (ft_strlen(tmp->value) > 15000)
		{
			g_exit = 1;
			return (1337);
		}
		tmp = tmp->next;
	}
	if (a > 16)
		return (0);
	return (1);
}

t_token *handele_herdoc(t_token *tk)
{
	t_token *tmp;
	t_token *new;
	static int a;
	void (*prev_handler)(int);
	prev_handler = signal(SIGINT, handle_signal_for_herdoc);
	new = NULL;
	tmp = tk;
	a = 0;
	while (tmp)
	{
		if (tmp->type == TYP_REDHERE)
		{
			change_herdoc_to_red(&new, &tmp, a);
			if (!new)
				break;
		}
		else
			add_token(&new, tmp->value, tmp->type, tmp->is_exp);
		if (tmp)
			tmp = tmp->next;
	}
	signal(SIGINT, handler_interactive);
	open("/dev/tty", O_RDONLY);
	if (!new)
		return NULL;
	a = 0;
	return new;
}
