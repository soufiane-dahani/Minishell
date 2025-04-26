/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export_help2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:26:37 by sodahani          #+#    #+#             */
/*   Updated: 2025/04/26 14:24:03 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *remove_plus(char *arg)
{
	int i = 0;
	int j = 0;
	char *new;

	new = ft_malloc(ft_strlen(arg) + 1, FT_ALLOC);
	while (arg[i])
	{
		if (arg[i] == '+' && arg[i + 1] == '=')
			i++;
		new[j++] = arg[i++];
	}
	new[j] = '\0';
	return (new);
}
void update_env_plus(char *var, char ***envp_ptr)
{
	int	idx;
	char *name_part;
	char *append_part;
	char *new_value;

	idx = env_var_index(var, *envp_ptr);
	if (idx != -1)
	{
		// Get value after '='
		append_part = ft_strchr(var, '=') + 1;
		// Join old value + new part
		new_value = ft_strjoin((*envp_ptr)[idx], append_part);
		(*envp_ptr)[idx] = new_value;
	}
	else
	{
		// If not found, need to insert like normal, without '+'
		name_part = remove_plus(var);
		append_env_var(name_part, envp_ptr);
	}
}
char	*ft_strdup_custom2(const char *s)
{
	size_t	len;
	int		i;
	char	*copy;
	int		k;
	len = ft_strlen(s);
	copy = ft_malloc(len + 1, FT_ALLOC);
	i = 0;
	k = 0;
	if (!copy)
		return (NULL);
	while(s[i])
	{
		if (s[k] == '+')
			k++;
		if (s[k] == '\0')
			break;
		copy[i] = s[k];
		i++;
		k++;
	}
	copy[i] = '\0';
	return (copy);
}
