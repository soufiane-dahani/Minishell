/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:07:54 by yaait-am          #+#    #+#             */
/*   Updated: 2025/04/29 09:24:38 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	help_herdoc(char **new, char *s)
{
	int (i), (a);
	i = 0;
	a = 0;
	while (s[i])
	{
		if (s[i] == '<' && s[i + 1] == '<')
		{
			(*new)[a++] = s[i++];
			(*new)[a++] = s[i++];
			while (s[i] && is_space(s[i]))
				(*new)[a++] = s[i++];
			if (s[i] == '"')
				i++;
			if (s[i] == '$')
				(*new)[a++] = '\'';
			while (s[i] && !is_token(s[i]) && s[i] != '"')
				(*new)[a++] = s[i++];
			if (s[i] == '"')
				i++;
			(*new)[a++] = '\'';
		}
		else
			(*new)[a++] = s[i++];
	}
	(*new)[a] = '\0';
}

char	*for_herdoc(char *s)
{
	int		i;
	int		a;
	char	*new;

	a = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '<' && s[i + 1] == '<')
		{
			i += 2;
			while (s[i] && is_space(s[i]))
				i++;
			if (s[i] == '"')
				i++;
			if (s[i] == '$')
				a++;
		}
		i++;
	}
	if (!a)
		return (s);
	new = ft_malloc(ft_strlen(s) + (a * 2) + 2, FT_ALLOC);
	help_herdoc(&new, s);
	return (new);
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
	data->s = for_herdoc(data->s);
	data->s = before_quote(data->s);
	if (!data->s)
		return (0);
	data->s = extra_work(data->s);
	split_the_cmd(data);
	tk = tokenize(data->cmd);
	tk = fix_the_case(tk);
	if (check_the_exp(tk))
		return (0);
	return (1);
}
