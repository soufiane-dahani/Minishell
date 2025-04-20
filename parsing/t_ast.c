/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_ast.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:42:19 by yaait-am          #+#    #+#             */
/*   Updated: 2025/04/20 16:12:01 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_token    *new_tk(t_token *tk)
{
    t_token    *s;
    t_token    *new;
    t_token    *pos;

    s = tk;
    new = NULL;
    while (s->type != TYP_REDOUT && s->type != TYP_REDIN)
    {
        add_token(&new, s->value, s->type);
        s = s->next;
    }
    pos = s;
    s = s->next;
    s = s->next;
    while (s)
    {
        add_token(&new, s->value, s->type);
        s = s->next;
    }
    add_token(&new, pos->value, pos->type);
	pos = pos->next;
    add_token(&new, pos->value, pos->type);
    return (new);
}

static t_token    *fix_the_case(t_token *tk)
{
    t_token    *s;
	t_token		*pos;

    s = tk;
    while (s && s->type != TYP_PIPE && s->type != TYP_AND && s->type != TYP_OR)
    {
        if (s->type == TYP_REDIN || s->type == TYP_REDOUT)
            break ;
        s = s->next;
    }
    if (!s || s->type == TYP_PIPE || s->type == TYP_AND || s->type == TYP_OR)
        return (tk);
    return (new_tk(tk));
}

t_ast	*build_the_tree(t_token *tk)
{
	t_ast	*node;
	int		npar;
	t_token	*op;
	t_token	*prev;

	node = NULL;
	npar = 0;
	prev = tk;
	op = NULL;
	while (prev)
	{
		if (prev->type == TYP_LPAR)
			npar++;
		if (prev->type == TYP_RPAR)
			npar--;
		if ((prev->type == TYP_AND || prev->type == TYP_PIPE
				|| prev->type == TYP_OR) && npar == 0)
			op = prev;
		prev = prev->next;
	}
	if (npar != 0)
		return (printf("invalid syntax near `('\n"), NULL);
	tk = fix_the_case(tk);
	node = start_for_ast(tk);
	return (node);
}
