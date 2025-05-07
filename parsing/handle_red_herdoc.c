/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_red_herdoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:21:20 by yaait-am          #+#    #+#             */
/*   Updated: 2025/05/07 15:35:09 by sodahani         ###   ########.fr       */
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
	int		result;

	total = ft_strdup("");
	delimiter = skip_quote(delimiter);
	while (1)
	{
		write(1, "> ", 2);
		result = get_next_line(&buffer);
		if (result < 0)
			return (NULL);
		if (result == 0 || ft_strcmp(buffer, delimiter) == 0)
			break ;
		total = ft_strjoin(total, buffer);
		total = ft_strjoin(total, "\n");
	}
	return (total);
}

void	change_herdoc_to_red(t_token **new, t_token **tmp, int a)
{
	char		*content;
	char		*delimiter;
	static char	*name;

	delimiter = NULL;
	if ((*tmp)->next)
		delimiter = (*tmp)->next->value;
	if (!a)
	{
		name = ft_strjoin("/tmp/", random_str());
		create_heredoc_tokens(new, name);
	}
	content = read_the_herdoc(delimiter);
	if (content == NULL)
	{
		*new = NULL;
		return ;
	}
	if (!process_heredoc_content(content, name, *tmp))
		return ;
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

t_token	*handele_herdoc(t_token *tk)
{
	t_token		*tmp;
	t_token		*new;
	static int	a;

	setup_signals();
	new = NULL;
	tmp = tk;
	a = 0;
	while (tmp)
	{
		if (!process_token(&new, &tmp, a))
			break ;
		if (tmp)
			tmp = tmp->next;
	}
	restore_signals();
	if (!new)
		return (NULL);
	a = 0;
	return (new);
}
