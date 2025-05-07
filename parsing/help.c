/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 10:08:18 by yaait-am          #+#    #+#             */
/*   Updated: 2025/05/07 15:30:00 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_valid_enclosure(t_token *start, t_token *end)
{
	t_token	*tmp;
	int		count;

	if (start->type != TYP_LPAR || end->type != TYP_RPAR)
		return (0);
	count = 0;
	tmp = start;
	while (tmp != end)
	{
		if (tmp->type == TYP_LPAR)
			count++;
		else if (tmp->type == TYP_RPAR)
			count--;
		if (count == 0 && tmp != end)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

t_token	*create_inner_tokens(t_token *start, t_token *end)
{
	t_token	*new;
	t_token	*tmp;

	new = NULL;
	tmp = start->next;
	while (tmp != end)
	{
		add_token(&new, tmp->value, tmp->type, tmp->is_exp);
		tmp = tmp->next;
	}
	return (new);
}

t_token	*create_token(char *value, t_type type, int exp)
{
	t_token	*new_token;

	new_token = ft_malloc(sizeof(t_token), FT_ALLOC);
	if (!new_token)
		return (NULL);
	new_token->value = ft_strdup(value);
	new_token->type = type;
	new_token->is_exp = exp;
	new_token->next = NULL;
	return (new_token);
}

char	*process_heredoc_content(char *content, char *name, t_token *tmp)
{
	int	fd;

	if (content == NULL)
		return (NULL);
	if (tmp->next && tmp->next->type != TYP_SQOUTE
		&& tmp->next->type != TYP_DQUOTE)
		content = exp_for_herdoc(content);
	fd = open(name, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	write(fd, content, ft_strlen(content));
	close(fd);
	return (content);
}

void	create_heredoc_tokens(t_token **new, char *name)
{
	add_token(new, "<", TYP_REDIN, 0);
	add_token(new, name, TYP_WORD, 0);
}
