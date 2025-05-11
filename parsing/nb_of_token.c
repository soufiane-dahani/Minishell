/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nb_of_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:08:25 by yaait-am          #+#    #+#             */
/*   Updated: 2025/05/11 16:43:10 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	nb_tok_special(char *str, int *i, int *count)
{
	char	quote;

	if (is_special_char(str[*i]) || str[*i] == '(' || str[*i] == ')')
	{
		(*count)++;
		(*i)++;
	}
	else if (str[*i] == '"' || str[*i] == '\'')
	{
		quote = str[*i];
		(*i)++;
		(*count)++;
		while (str[*i] && str[*i] != quote)
			(*i)++;
		if (str[*i] == quote)
			(*i)++;
	}
}

int	nb_tok(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && is_space(str[i]))
			i++;
		if (!str[i])
			break ;
		if (is_special_char(str[i]) || str[i] == '(' || str[i] == ')'
			|| str[i] == '"' || str[i] == '\'')
			nb_tok_special(str, &i, &count);
		else
		{
			count++;
			while (str[i] && !is_space(str[i]) && !is_special_char(str[i])
				&& str[i] != '(' && str[i] != ')' && str[i] != '"'
				&& str[i] != '\'')
				i++;
		}
	}
	return (count++, count);
}

int	calcule_the_cmd(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	return (i);
}

int	is_only_flg(char *s)
{
	int	i;

	i = 1;
	if (s[0] != '-')
		return (0);
	while (s[i] && s[i] == 'n')
		i++;
	if (s[i])
		return (0);
	return (1);
}

char	**fix_the_issuse_with_echo(char **cmd)
{
	int		a;
	int		i;
	char	**new;

	a = 0;
	i = 0;
	new = ft_malloc((calcule_the_cmd(cmd) + 1) * sizeof(char *), FT_ALLOC);
	new[a++] = cmd[i++];
	if (is_only_flg(cmd[i]))
		new[a++] = ft_strdup("-n");
	while (cmd[i] && is_only_flg(cmd[i]))
		i++;
	while (cmd[i])
		new[a++] = cmd[i++];
	new[a] = NULL;
	return (new);
}
