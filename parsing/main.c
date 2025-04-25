/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:07:54 by yaait-am          #+#    #+#             */
/*   Updated: 2025/04/25 15:19:14 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parsing(t_cmd *data)
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
	data->s = before_quote(data->s);
	if (!data->s)
		return (0);
	split_the_cmd(data);
	tk = tokenize(data->cmd);
	tk = fix_the_case(tk);
	if (check_the_exp(tk))
		return (0);
	return (1);
}
