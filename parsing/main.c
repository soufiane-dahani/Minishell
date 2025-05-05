/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:07:54 by yaait-am          #+#    #+#             */
/*   Updated: 2025/05/05 07:55:19 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	the_quote_are_even(char *s)
{
	int	i;
	int	single;
	int	doubl;

	i = 0;
	single = 0;
	doubl = 0;
	while (s[i])
	{
		if (s[i] == '"')
			doubl++;
		if (s[i] == '\'')
			single++;
		i++;
	}
	if ((single % 2) || (doubl % 2))
	{
		printf("invalid syntax\n");
		return (0);
	}
	return (1);
}

int	parsing(t_cmd *data, t_ast **node)
{
	int		i;
	t_token	*tk;

	i = 0;
	if (data->s == NULL)
	{
		printf("exit\n");
		ft_malloc(0, FT_CLEAR);
		rl_clear_history();
		exit(0);
	}
	if (!the_quote_are_even(data->s))
	{
		the_exit = 1;
		return (0);
	}
	split_the_cmd(data);
	tk = tokenize(data->cmd);
	if (!is_cmd_valid(tk, node))
	{
		the_exit = 1;
		return (0);
	}
	return (1);
}
