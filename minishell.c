/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:46:14 by yaait-am          #+#    #+#             */
/*   Updated: 2025/04/27 19:06:27 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*g_ast;

void	ft_clear_work(t_cmd *data, char ***env, t_export_store *store)
{
	if (!parsing(data))
		return ;
	g_ast->exit_status = execute_ast(g_ast, env, store);
}

int	main(int ac, char **av, char **env)
{
	t_cmd			*data;
	char			**env_copy;
	t_export_store	*store;

	store = ft_malloc(sizeof(t_export_store), FT_ALLOC);
	if (!store)
		return (1);
	store->vars = NULL;
	(void)av;
	if (ac != 1)
	{
		printf("\n [ ==> Usage: ./minishell <== ]\n\n");
		return (1);
	}
	if (env[0] == NULL)
		env = add_new_env_if_not_found();
	env_copy = copy_env(env);
	add_shlvl(&env_copy);
	g_ast = ft_malloc(sizeof(t_ast), FT_ALLOC);
	g_ast->exit_status = 0;
	while (1)
	{
		setup_interactive_signals();
		data = ft_malloc(sizeof(t_cmd), FT_ALLOC);
		data->s = readline("minishell$> ");
		add_history(data->s);
		ft_clear_work(data, &env, store);
		ft_malloc(0, FT_CLEAR);
	}
}
