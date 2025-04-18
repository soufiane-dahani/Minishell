/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:46:14 by yaait-am          #+#    #+#             */
/*   Updated: 2025/04/18 10:26:49 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*g_ast;

void	ft_clear_work(t_cmd *data, char ***env)
{
	if (!parsing(data))
		return ;
	execute_ast(env);
}

int	main(int ac, char **av, char **env)
{
	t_cmd	*data;
	char	**env_copy;

	(void)av;
	data = ft_malloc(sizeof(t_cmd), FT_ALLOC);
	signal(SIGINT, handler);
	if (ac != 1)
	{
		printf("\n [ ==> Usage: ./minishell <== ]\n\n");
		free(data);
		return (1);
	}
	env_copy = copy_env(env); // <-- this is the fix
	while (1)
	{
		data->s = readline("minishell$> ");
		add_history(data->s);
		ft_clear_work(data, &env_copy);
		free(data->s);
	}
}
