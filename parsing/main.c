/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:07:54 by yaait-am          #+#    #+#             */
/*   Updated: 2025/04/24 17:45:10 by yaait-am         ###   ########.fr       */
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
	{
		printf("%s - %d - %d", node->cmd[0],
			node->exp, node->type);
		for (int i = 1; node->cmd[i]; i++)
			printf(" --> %s", node->cmd[i]);
		printf("\n");
	}
	else
		printf("(NULL CMD)\n");
	print_ast(node->l, level + 8);
}

int	parsing(t_cmd *data)
{
	int		i;
	t_token	*tk;

	i = 0;
	if (data->s == NULL)
	{
		printf("exit\n");
		ft_malloc(0, FT_CLEAR);
		rl_clear_history();
		exit(0);
	}
	data->s = before_quote(data->s);
	if (!data->s)
		return (0);
	split_the_cmd(data);
	tk = tokenize(data->cmd);
	tk = fix_the_case(tk);
	if (check_the_exp(tk))
		return (0);
	print_ast(g_ast, 2);
	return (1);
}
