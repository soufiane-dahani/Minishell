/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_the_linked.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:13:54 by yaait-am          #+#    #+#             */
/*   Updated: 2025/05/07 15:28:11 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_token(t_token **head, char *value, t_type type, int exp)
{
	t_token	*new_token;
	t_token	*temp;

	new_token = create_token(value, type, exp);
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
	else if (is_couple(str))
		return (TYP_DQUOTE);
	else if (is_single(str))
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
		add_token(&head, cmd[i], type, 0);
		i++;
	}
	return (head);
}

t_token	*handle_invalid_syntax_for_hardoc(t_token *tk)
{
	t_token	*tmp;
	t_token	*new;

	tmp = tk;
	new = NULL;
	while (tmp)
	{
		if (tmp->type == TYP_REDHERE && (!tmp->next
				|| is_token_nor(tmp->next->type)
				|| is_token_sep(tmp->next->type)))
		{
			printf("invalid syntax near `<<'\n");
			break ;
		}
		add_token(&new, tmp->value, tmp->type, tmp->is_exp);
		tmp = tmp->next;
	}
	return (new);
}

t_token	*fixing(t_token *tk)
{
	check_the_exp(&tk);
	tk = handle_invalid_syntax_for_hardoc(tk);
	tk = fix_the_case(tk);
	if (!calcul_herdoc(tk))
	{
		printf("the number of herdoc is too much\n");
		ft_malloc(0, FT_CLEAR);
		exit(2);
	}
	if (calcul_herdoc(tk) == 1337)
	{
		printf("the len of the arg is too tall\n");
		return (NULL);
	}
	tk = handele_herdoc(tk);
	return (tk);
}
