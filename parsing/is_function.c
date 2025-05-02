/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 10:11:44 by yaait-am          #+#    #+#             */
/*   Updated: 2025/05/02 15:43:42 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_space(char c)
{
	return (c == ' ' || c == '\n' || c == '\t');
}

int	is_token_sep(t_type s)
{
	return (s == TYP_AND || s == TYP_PIPE || s == TYP_OR);
}

int	is_token(char c)
{
	return (c == '|' || c == '&'
		|| c == '>' || c == '<'
		|| is_space(c));
}

int	is_special_char(char c)
{
	return (c == '|' || c == '&' || c == '<' || c == '>'
		|| c == '(' || c == ')');
}

int	ft_isalnum(int c)
{
	return ((c >= 'A' && c <= 'Z')
		|| (c >= 'a' && c <= 'z'));
}
