/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_red_herdoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:21:20 by yaait-am          #+#    #+#             */
/*   Updated: 2025/05/05 14:38:10 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	get_next_line(char **line)
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

static char	*read_the_herdoc(char *delimiter)
{
	char	*buffer;
	char	*total;

	total = ft_strdup("");
	delimiter = skip_quote(delimiter);
	while (1)
	{
		write(1, "> ", 2);
		if (get_next_line(&buffer) <= 0)
			break ;
		if (ft_strcmp(buffer, delimiter) == 0)
			break ;
		total = ft_strjoin(total, buffer);
		total = ft_strjoin(total, "\n");
	}
	return (total);
}

static void	change_herdoc_to_red(t_token **new, t_token **tmp, int a)
{
	char		*content;
	char		*delimeter;
	int			fd;
	static char	*name;

	delimeter = NULL;
	if ((*tmp)->next)
		delimeter = (*tmp)->next->value;
	if (!a)
	{
		name = ft_strjoin("/tmp/", random_str());
		add_token(new, "<", TYP_REDIN, 0);
		add_token(new, name, TYP_WORD, 0);
	}
	content = read_the_herdoc(delimeter);
	if ((*tmp)->next->type != TYP_SQOUTE && (*tmp)->next->type != TYP_DQUOTE)
		content = exp_for_herdoc(content);
	fd = open(name, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	write (fd, content, ft_strlen(content));
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
		tmp = tmp->next;
	}
	if (a > 16)
		return (0);
	return (1);
}

t_token	*handele_herdoc(t_token *tk)
{
	t_token			*tmp;
	t_token			*new;
	static int		a;

	(1) && (new = NULL), (tmp = tk);
	if (!calcul_herdoc(tk))
		return (printf("the number of herdoc is too much\n"), NULL);
	a = 0;
	while (tmp)
	{
		if (tmp->type == TYP_REDHERE)
			change_herdoc_to_red(&new, &tmp, a);
		else
			add_token(&new, tmp->value, tmp->type, tmp->is_exp);
		if (tmp)
			tmp = tmp->next;
	}
	return (a = 0, new);
}
