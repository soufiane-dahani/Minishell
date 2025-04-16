/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:07:54 by yaait-am          #+#    #+#             */
/*   Updated: 2025/04/16 17:52:40 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	print_indent(int level)
{
	for (int i = 0; i < level; i++)
		printf("  ");
}

static void	print_ast(t_ast *node, int level)
{
	if (!node)
		return ;
	print_ast(node->r, level + 8);
	print_indent(level);
	if (node->cmd && node->cmd[0])
		printf(" [ ==> %s - %d - %d <== ]\n", node->cmd[0],
			node->exp, node->type);
	else
		printf("(NULL CMD)\n");
	print_ast(node->l, level + 8);
}

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
		rl_clear_history();
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
	print_ast(g_ast, 5);
}
