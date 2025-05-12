/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:07:54 by yaait-am          #+#    #+#             */
/*   Updated: 2025/05/12 14:52:13 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	the_quote_are_even(char *s)
{
	int		i;
	char	q;

	i = 0;
	while (s[i])
	{
		if (s[i] == '"' || s[i] == '\'')
		{
			q = s[i];
			i++;
			while (s[i] && s[i] != q)
				i++;
			if (!s[i])
			{
				printf("invalid syntax\n");
				return (0);
			}
		}
		i++;
	}
	return (1);
}
// static void	print_indent(int level)
// {
// 	for (int i = 0; i < level; i++)
// 		printf("  ");
// }

// static void	print_ast(t_ast *node, int level)
// {
// 	if (!node)
// 		return ;
// 	print_ast(node->r, level + 8);
// 	print_indent(level);
// 	if (node->cmd && node->cmd[0])
// 	{
// 		printf("%s - %d - %d", node->cmd[0],
// 			node->exp, node->type);
// 		for (int i = 1; node->cmd[i]; i++)
// 			printf(" --> %s", node->cmd[i]);
// 		printf("\n");
// 	}
// 	else
// 		printf("(NULL CMD)\n");
// 	print_ast(node->l, level + 8);
// }

int	parsing(t_cmd *data, t_ast **node)
{
	t_token	*tk;

	if (data->s == NULL)
	{
		printf("exit\n");
		ft_malloc(0, FT_CLEAR);
		rl_clear_history();
		exit(0);
	}
	if (!the_quote_are_even(data->s))
	{
		g_exit = 2;
		return (0);
	}
	if (!data->s[0])
	{
		g_exit = 0;
		return (0);
	}
	split_the_cmd(data);
	tk = tokenize(data->cmd);
	if (!is_cmd_valid(tk, node))
		return (g_exit = 2, 0);
	// print_ast(*node , 5);
	return (1);
}

int	process_token(t_token **new, t_token **tmp, int a)
{
	if ((*tmp)->type == TYP_REDHERE)
	{
		change_herdoc_to_red(new, tmp, a);
		if (!(*new))
			return (0);
	}
	else
		add_token(new, (*tmp)->value, (*tmp)->type, (*tmp)->is_exp);
	return (1);
}

void	restore_signals(void)
{
	signal(SIGINT, handler_interactive);
	open("/dev/tty", O_RDONLY);
}
