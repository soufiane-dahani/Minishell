/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:46:14 by yaait-am          #+#    #+#             */
/*   Updated: 2025/04/16 17:58:28 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*g_ast;

int	main(int ac, char **av)
{
	t_cmd	*data;

	(void)av;
	data = ft_malloc(sizeof(t_cmd), FT_ALLOC);
	signal(SIGINT, handler);
	// signal(SIGQUIT, SIG_IGN);
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
