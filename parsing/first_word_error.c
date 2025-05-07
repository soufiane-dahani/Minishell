/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_word_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:24:37 by yaait-am          #+#    #+#             */
/*   Updated: 2025/05/05 16:16:29 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_the_first(t_token *tk)
{
	if (!tk)
		return (0);
	if (invalid_syntax(tk))
		return (0);
	return (1);
}

int	invalid_syntax(t_token *tk)
{
	if (tk->type == TYP_OR || tk->type == TYP_RPAR || tk->type == TYP_AND
		|| tk->type == TYP_PIPE)
	{
		printf("invalid syntax near '%s'\n", tk->value);
		return (1);
	}
	while (tk->next)
		tk = tk->next;
	if (tk->type != TYP_WORD && tk->type != TYP_DQUOTE && tk->type != TYP_SQOUTE
		&& tk->type != TYP_RPAR)
	{
		printf("invalid syntax near '%s'\n", tk->value);
		return (1);
	}
	return (0);
}

int	is_hide(char *s)
{
	if (s[0] == '.')
		return (1);
	return (0);
}

t_token	*handle_wildcard(t_token *tk)
{
	t_token	*s;
	t_token	*new;
	t_token	*tokens;

	s = tk;
	new = NULL;
	while (s)
	{
		if (s->type == TYP_WORD && ft_strchr(s->value, '*'))
		{
			if (s->value[strlen(s->value) - 1] == '/' && strchr(s->value, '*'))
				expand_to_directories(s->value, &new);
			else
			{
				tokens = change_the_cards(s->value);
				help_wildcard(tokens, &new, s);
			}
		}
		else
			add_token(&new, s->value, s->type, 0);
		s = s->next;
	}
	return (new);
}

int	is_exit(char **new, int *i, char *s, int *old)
{
	char	*helper;
	int		j;

	if (!s[(*i)] || s[(*i)] == '"' || s[(*i)] == '?' || !ft_isalnum(s[(*i)]))
	{
		if (s[(*i)] == '?')
		{
			helper = ft_itoa(g_exit);
			j = 0;
			while (helper[j])
				(*new)[(*old)++] = helper[j++];
			(*i)++;
			return (1);
		}
		(*new)[(*old)++] = '$';
		return (1);
	}
	return (0);
}
