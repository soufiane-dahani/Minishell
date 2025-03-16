/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:07:54 by yaait-am          #+#    #+#             */
/*   Updated: 2025/03/11 11:25:56 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing(t_cmd *data)
{
	int	i;
	t_token	*tk;

	i = 0;
	if (data->s == NULL || !ft_strncmp(data->s, "exit", 5))
	{
		printf("exit\n");
		while (i != 199999991)
			i++;
		ft_malloc(0, FT_CLEAR);
		exit(0);
	}
	more_parsing(data);
	i = 0;
	while (data->cmd[i])
	{
		printf("Token %d: %s\n", i, data->cmd[i]);
		i++;
	}
	tk = tokenize(data->cmd);
	(void)tk;
}

int	main(int ac, char **av)
{
	t_cmd	*data;

	(void)av;
	data = malloc(sizeof(t_cmd));
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	if (ac != 1)
	{
		printf("\n [ ==> Usage: ./minishell <== ]\n\n");
		free(data);
		return (1);
	}
	while (1)
	{
		data->s = readline("minishell$> ");
		add_history(data->s);
		parsing(data);
		free(data->s);
	}
}
