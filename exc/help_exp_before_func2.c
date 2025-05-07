/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_exp_before_func2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:26:07 by yaait-am          #+#    #+#             */
/*   Updated: 2025/05/07 15:21:21 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	process_string(char **new, char *str, int *matches)
{
	if (has_wildcard_char(str))
		add_matches(new, str, matches);
	else
		new[(*matches)++] = ft_strdup(str);
}
