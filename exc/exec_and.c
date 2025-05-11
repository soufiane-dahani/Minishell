/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_and.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:26:37 by sodahani          #+#    #+#             */
/*   Updated: 2025/05/11 18:24:07 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_and(t_ast *node, char ***envp, t_export_store *store)
{
	int	left_status;

	if (!node || node->type != TYP_AND)
		return (1);
	left_status = execute_ast(node->l, envp, store);
	if (left_status == 0)
		return (execute_ast(node->r, envp, store));
	return (left_status);
}

int	exec_or(t_ast *node, char ***envp, t_export_store *store)
{
	int	left_status;

	if (!node || node->type != TYP_OR)
		return (1);
	left_status = execute_ast(node->l, envp, store);
	if (left_status != 0)
		return (execute_ast(node->r, envp, store));
	return (left_status);
}
