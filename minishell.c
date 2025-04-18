/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:46:14 by yaait-am          #+#    #+#             */
/*   Updated: 2025/04/19 12:26:52 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*g_ast;

void	ft_clear_work(t_cmd *data, char ***env)
{
	if (!parsing(data))
		return ;
	(void)env;
}

int	main(int ac, char **av, char **env)
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
		ft_clear_work(data, &env);
	}
}
