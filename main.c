/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:07:54 by yaait-am          #+#    #+#             */
/*   Updated: 2025/03/24 15:31:40 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast *g_ast = NULL;

void	parsing(t_cmd *data)
{
	int		i;
	t_token	*tk;

	i = 0;
	if (data->s == NULL || !ft_strncmp(data->s, "exit", 5))
	{
		printf("exit\n");
		while (i != 199999991)
			i++;
		ft_malloc(0, FT_CLEAR);
		free(data->s);
		exit(0);
	}
	split_the_cmd(data);
	tk = tokenize(data->cmd);
	if (check_the_exp(tk))
		return ;
	while (tk)
	{
		printf("tk : %s ---> typ : %u ----> exp :% d\n", tk->value,
			tk->type, tk->is_exp);
		tk = tk->next;
	}
	while (g_ast)
	{
		printf("g_ast : %s ---> typ : %u ----> exp :% d\n", g_ast->cmd[0],
			g_ast->type, g_ast->exp);
		g_ast = g_ast->next;
	}
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
