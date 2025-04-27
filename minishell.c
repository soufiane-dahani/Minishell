/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:46:14 by yaait-am          #+#    #+#             */
/*   Updated: 2025/04/27 15:03:38 by yaait-am         ###   ########.fr       */
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
	if (ac != 1)
	{
		printf("\n [ ==> Usage: ./minishell <== ]\n\n");
		return (1);
	}
	while (1)
	{
		g_ast = ft_malloc(sizeof(t_ast), FT_ALLOC);
		g_ast->exit_status = 0;
		setup_interactive_signals();
		data = ft_malloc(sizeof(t_cmd), FT_ALLOC);
		data->s = readline("minishell$> ");
		add_history(data->s);
		ft_clear_work(data, &env);
		ft_malloc(0, FT_CLEAR);
	}
}
