/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_worderr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:24:37 by yaait-am          #+#    #+#             */
/*   Updated: 2025/04/22 10:02:12 by yaait-am         ###   ########.fr       */
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
	if (tk->type == TYP_OR || tk->type == TYP_RPAR
		|| tk->type == TYP_AND || tk->type == TYP_PIPE)
	{
		printf("invalid syntax near '%s'\n", tk->value);
		return (1);
	}
	while (tk->next)
		tk = tk->next;
	if (tk->type != TYP_WORD && tk->type != TYP_DQUOTE
		&& tk->type != TYP_SQOUTE && tk->type != TYP_RPAR)
	{
		printf("invalid syntax near '%s'\n", tk->value);
		return (1);
	}
	return (0);
}

int	is_root(char *cmd)
{
	int		i;
	char	*cd;

	if (!cmd)
		return (0);
	i = ft_strlen(cmd);
	if (cmd[0] == '/' || cmd[0] == '-')
	{
		printf("bash: %s: command not found\n", cmd);
		return (1);
	}
	if (cmd[0] == '\\')
	{
		if (i % 2)
			return (1);
		cd = ft_malloc((i / 2) + 1, FT_ALLOC);
		if (!cd)
			return (1);
		ft_memset(cd, '\\', i / 2);
		cd[i / 2] = '\0';
		printf("bash: %s: command not found\n", cd);
		return (1);
	}
	return (0);
}

static void	help_wildcard(t_token *tokens, t_token **new, t_token *s)
{
	if (tokens)
	{
		while (tokens)
		{
			add_token(new, tokens->value, tokens->type, 0);
			tokens = tokens->next;
		}
	}
	else
		add_token(new, s->value, s->type, 0);
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
			tokens = change_the_cards(s->value);
			help_wildcard(tokens, &new, s);
		}
		else
			add_token(&new, s->value, s->type, 0);
		s = s->next;
	}
	return (new);
}
