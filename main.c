/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 09:32:09 by yaait-am          #+#    #+#             */
/*   Updated: 2025/02/26 15:36:17 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid(t_cmd *data)
{
	int	i;
	int	a;

	i = 0;
	a = 0;
	data->cmd = ft_split(data->s, '|');
	while (data->cmd[i])
	{
		data->all = handle_quote(data->cmd[i]);
		if (check_is_valid(data))
			a = 1;
		add_history(data->s);
		i++;
	}
	return (a);
}

void	parsing(t_cmd *data)
{
	int	i;

	i = 0;
	if (data->s == NULL || !ft_strncmp(data->s, "exit", 5))
	{
		printf("exit\n");
		while (i != 199999991)
			i++;
		free(data);
		exit(0);
	}
	if (is_valid(data))
		return ;
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
		parsing(data);
	}
}
