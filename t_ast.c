/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_ast.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:42:19 by yaait-am          #+#    #+#             */
/*   Updated: 2025/03/07 14:33:00 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	convert_to_tree(t_cmd *data)
// {
// 	int	i;

// 	i = 0;
// 	find_the_head(data);
// 	while (data->cmd[i])
// 	{
// 		i++;
// 	}
// }

// void	find_the_head(t_cmd *data)
// {
// 	int	i;

// 	i = 0;
// 	while (data->cmd[i])
// 	{
// 		check_the_head(data);
// 	}
// }

t_ast	*new_ast_node(char *value)
{
	t_ast	*node;

	node = ft_malloc(sizeof(t_ast), FT_ALLOC);
	if (!node)
		return (NULL);
	node->value = ft_strdup(value);
	node->l = NULL;
	node->r = NULL;
	return (node);
}
