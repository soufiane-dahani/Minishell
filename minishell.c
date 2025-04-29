/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:46:14 by yaait-am          #+#    #+#             */
/*   Updated: 2025/04/29 19:04:47 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*g_ast;

void	ft_clear_work(t_cmd *data, char ***env, t_export_store *store)
{
	if (!parsing(data))
		return ;
	g_ast->exit_status = execute_ast(g_ast, env, store);
	g_ast->sign = 0;
}

int	main(int ac, char **av, char **env)
{
	t_cmd			*data;
	char			**env_copy;
	t_export_store	*store;

	(void)av;
	if (ac != 1)
	{
		printf("\n [ ==> Usage: ./minishell <== ]\n\n");
		return (1);
	}
	if (env[0] == NULL)
		env = add_new_env_if_not_found();
	g_ast = ft_malloc(sizeof(t_ast), FT_ALLOC);
	g_ast->exit_status = 0;
	env_copy = copy_env(env);
	add_shlvl(&env_copy);
	data = ft_malloc(sizeof(t_cmd), FT_ALLOC);
	store = ft_malloc(sizeof(t_export_store), FT_ALLOC);
	if (!store)
		return (1);
	store->vars = NULL;
	g_ast->env = env_copy;
	setup_interactive_signals();
	while (1)
	{
		g_ast->sign = 1;
		data->s = readline("minishell$> ");
		add_history(data->s);
		ft_clear_work(data, &env_copy, store);
	}
}
