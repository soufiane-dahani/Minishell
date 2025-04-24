/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:46:14 by yaait-am          #+#    #+#             */
/*   Updated: 2025/04/24 14:48:37 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*g_ast;

void	ft_clear_work(t_cmd *data, char ***env, t_export_store *store)
{
	int i;
	if (!parsing(data))
		return ;
	i = execute_ast(g_ast, env, store);
}

int	main(int ac, char **av, char **env)
{
	t_cmd	*data;
	char	**env_copy;
	t_export_store *store = ft_malloc(sizeof(t_export_store), FT_ALLOC);
	if (!store)
		return (1);
	store->vars = NULL;

	(void)av;
	data = ft_malloc(sizeof(t_cmd), FT_ALLOC);
	signal(SIGINT, handler);
	if (ac != 1)
	{
		printf("\n [ ==> Usage: ./minishell <== ]\n\n");
		free(data);
		return (1);
	}
	if (env[0] == NULL)
		env = add_new_env_if_not_found();
	env_copy = copy_env(env);
	add_shlvl(&env_copy);
	while (1)
	{
		data->s = readline("minishell$> ");
		add_history(data->s);
		ft_clear_work(data, &env_copy, store);
	}
}
