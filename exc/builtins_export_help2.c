/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export_help2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:26:37 by sodahani          #+#    #+#             */
/*   Updated: 2025/04/26 14:41:51 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*remove_plus(char *arg)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
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

void	update_env_plus(char *var, char ***envp_ptr)
{
	int		idx;
	char	*name_part;
	char	*append_part;
	char	*new_value;

	idx = env_var_index(var, *envp_ptr);
	if (idx != -1)
	{
		append_part = ft_strchr(var, '=') + 1;
		new_value = ft_strjoin((*envp_ptr)[idx], append_part);
		(*envp_ptr)[idx] = new_value;
	}
	else
	{
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
	while (s[i])
	{
		if (s[k] == '+')
			k++;
		if (s[k] == '\0')
			break ;
		copy[i] = s[k];
		i++;
		k++;
	}
	copy[i] = '\0';
	return (copy);
}

void	add_or_update_env(char *arg, char ***envp_ptr)
{
	int		idx;
	char	*clean_arg;

	clean_arg = remove_plus(arg);
	idx = env_var_index(clean_arg, *envp_ptr);
	if (idx != -1)
	{
		(*envp_ptr)[idx] = ft_strdup_custom(clean_arg);
	}
	else
		append_env_var(clean_arg, envp_ptr);
}
