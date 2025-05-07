/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_function_for_tree.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 11:52:21 by yaait-am          #+#    #+#             */
/*   Updated: 2025/05/07 15:27:24 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**tokens_to_cmd_array(t_token *tk)
{
	int		count;
	t_token	*tmp;
	char	**cmd;
	int		i;

	count = 0;
	tmp = tk;
	while (tmp && !is_token_nor(tmp->type) && tk->type != TYP_RPAR)
	{
		count++;
		tmp = tmp->next;
	}
	cmd = ft_malloc(sizeof(char *) * (count + 1), FT_ALLOC);
	if (!cmd)
		return (NULL);
	tmp = tk;
	i = 0;
	while (tmp && !is_token_nor(tmp->type) && tmp->type != TYP_RPAR)
	{
		cmd[i++] = ft_strdup(tmp->value);
		tmp = tmp->next;
	}
	cmd[i] = NULL;
	return (cmd);
}

void	creat_the_cmd(t_ast **node, t_token **tk)
{
	(*node) = ft_malloc(sizeof(t_ast), FT_ALLOC);
	(*node)->l = NULL;
	(*node)->r = NULL;
	(*node)->redir = NULL;
	(*node)->cmd = tokens_to_cmd_array(*tk);
	(*node)->exp = (*tk)->is_exp;
	(*node)->type = (*tk)->type;
	while ((*tk) && !is_token_nor((*tk)->type) && (*tk)->type != TYP_RPAR)
		(*tk) = (*tk)->next;
	if ((*tk) && (*tk)->type == TYP_RPAR)
		(*tk) = (*tk)->next;
	while ((*tk))
	{
		if ((*tk) && (*tk)->type != TYP_RPAR)
			add_token(&(*node)->redir, (*tk)->value, (*tk)->type,
				(*tk)->is_exp);
		(*tk) = (*tk)->next;
	}
}

unsigned int	ft_rand(void)
{
	unsigned int	num;
	int				fd;

	num = 0;
	fd = open("/dev/urandom", O_RDONLY);
	if (fd < 0)
		return (42);
	if (read(fd, &num, sizeof(num)) != sizeof(num))
		num = 1337;
	close(fd);
	return (num);
}

char	*random_str(void)
{
	int		length;
	char	*str;
	int		i;

	length = 5 + (ft_rand() % 11);
	str = ft_malloc(length + 1, FT_ALLOC);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (i < length)
	{
		str[i] = 'a' + (ft_rand() % 26);
		i++;
	}
	str[length] = '\0';
	return (str);
}
