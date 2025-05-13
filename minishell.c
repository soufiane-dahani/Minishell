/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:46:14 by yaait-am          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/05/09 10:01:39 by yaait-am         ###   ########.fr       */
=======
/*   Updated: 2025/04/28 19:03:07 by yaait-am         ###   ########.fr       */
>>>>>>> dahani
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

<<<<<<< HEAD
int		g_exit;

void	ft_clear_work(t_cmd *data, char ***env, t_export_store *store,
		t_ast **node)
{
	if (!parsing(data, node))
		return ;
	g_exit = execute_ast(*node, env, store);
}

static int	initialize_shell(t_cmd **data, t_export_store **store, t_ast **node)
{
	*node = ft_malloc(sizeof(t_ast), FT_ALLOC);
	g_exit = 0;
	*data = ft_malloc(sizeof(t_cmd), FT_ALLOC);
	*store = ft_malloc(sizeof(t_export_store), FT_ALLOC);
	if (!(*store))
		return (1);
	(*store)->vars = NULL;
	return (0);
}

static int	check_arguments(int ac)
{
	if (ac != 1)
	{
		printf("\n [ ==> Usage: ./minishell <== ]\n\n");
		return (1);
	}
	return (0);
}

static void	shell_loop(t_cmd *data, char **env_copy,
			t_export_store *store, t_ast **node)
{
	while (1)
	{
		my_getenv(NULL, env_copy);
		setup_interactive_signals();
		data->s = readline("$ ");
		add_history(data->s);
		ft_clear_work(data, &env_copy, store, node);
	}
=======
t_ast	*g_ast;

void	ft_clear_work(t_cmd *data, char ***env, t_export_store *store)
{
	if (!parsing(data))
		return ;
	g_ast->exit_status = execute_ast(g_ast, env, store);
>>>>>>> dahani
}

int	main(int ac, char **av, char **env)
{
	t_cmd			*data;
	char			**env_copy;
	t_export_store	*store;
<<<<<<< HEAD
	t_ast			*node;

	(void)av;
	if (check_arguments(ac))
		return (1);
	if (env[0] == NULL)
		env = add_new_env_if_not_found();
	env_copy = copy_env(env);
	add_shlvl(&env_copy);
	if (initialize_shell(&data, &store, &node))
		return (1);
	shell_loop(data, env_copy, store, &node);
	return (0);
=======

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
	while (1)
	{
		setup_interactive_signals();
		data->s = readline("minishell$> ");
		add_history(data->s);
		ft_clear_work(data, &env_copy, store);
	}
>>>>>>> dahani
}
