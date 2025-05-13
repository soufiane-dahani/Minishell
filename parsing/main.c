/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:07:54 by yaait-am          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/05/12 18:27:52 by yaait-am         ###   ########.fr       */
=======
/*   Updated: 2025/04/28 17:13:08 by yaait-am         ###   ########.fr       */
>>>>>>> dahani
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

<<<<<<< HEAD
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

int	parsing(t_cmd *data, t_ast **node)
{
	t_token	*tk;

=======
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


int	parsing(t_cmd *data)
{
	int		i;
	t_token	*tk;

	i = 0;
>>>>>>> dahani
	if (data->s == NULL)
	{
		printf("exit\n");
		ft_malloc(0, FT_CLEAR);
		rl_clear_history();
		exit(0);
	}
<<<<<<< HEAD
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
=======
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
>>>>>>> dahani
