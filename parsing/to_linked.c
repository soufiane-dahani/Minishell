/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_linked.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:13:54 by yaait-am          #+#    #+#             */
/*   Updated: 2025/04/17 14:36:22 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*create_token(char *value, t_type type)
{
	t_token	*new_token;

	new_token = ft_malloc(sizeof(t_token), FT_ALLOC);
	if (!new_token)
		return (NULL);
	new_token->value = ft_strdup(value);
	new_token->type = type;
	new_token->next = NULL;
	return (new_token);
}

void	add_token(t_token **head, char *value, t_type type)
{
	t_token	*new_token;
	t_token	*temp;

	new_token = create_token(value, type);
	if (!new_token)
		return ;
	if (!*head)
		*head = new_token;
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new_token;
	}
}

static t_type	get_token_type(char *str)
{
	if (ft_strncmp(str, "|", 2) == 0)
		return (TYP_PIPE);
	else if (ft_strncmp(str, "&&", 3) == 0)
		return (TYP_AND);
	else if (ft_strncmp(str, "||", 3) == 0)
		return (TYP_OR);
	else if (ft_strncmp(str, "<", 2) == 0)
		return (TYP_REDIN);
	else if (ft_strncmp(str, ">", 2) == 0)
		return (TYP_REDOUT);
	else if (ft_strncmp(str, "<<", 3) == 0)
		return (TYP_REDHERE);
	else if (ft_strncmp(str, ">>", 3) == 0)
		return (TYP_REDAPP);
	else if (str[0] == '(')
		return (TYP_LPAR);
	else if (str[0] == ')')
		return (TYP_RPAR);
	else if (str[0] == '"')
		return (TYP_DQUOTE);
	else if (str[0] == '\'')
		return (TYP_SQOUTE);
	else
		return (TYP_WORD);
}

t_token	*tokenize(char **cmd)
{
	t_token	*head;
	int		i;
	t_type	type;

	head = NULL;
	i = 0;
	while (cmd[i])
	{
		type = get_token_type(cmd[i]);
		add_token(&head, cmd[i], type);
		i++;
	}
	return (head);
}
