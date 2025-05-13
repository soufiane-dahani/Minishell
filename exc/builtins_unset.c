/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:26:37 by sodahani          #+#    #+#             */
/*   Updated: 2025/05/11 21:52:55 by sodahani         ###   ########.fr       */
=======
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:26:37 by sodahani          #+#    #+#             */
/*   Updated: 2025/04/27 20:10:32 by yaait-am         ###   ########.fr       */
>>>>>>> dahani
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
<<<<<<< HEAD
#include <string.h>
=======
>>>>>>> dahani

int	is_valid_identifier(char *name)
{
	int	i;

	i = 0;
	if (!name || !name[0])
		return (0);
	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (0);
	i = 1;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static int	count_env_variables(char **env)
{
	int	count;

	count = 0;
	while (env[count])
		count++;
	return (count);
}

void	remove_env_var(int idx, char ***envp_ptr)
{
	int		i;
	int		j;
	char	**env;
	char	**new_env;
	int		count;

	env = *envp_ptr;
	count = count_env_variables(env);
	new_env = ft_malloc((sizeof(char *) * count), FT_ALLOC);
	if (!new_env)
		return ;
	i = 0;
	j = 0;
	while (env[i])
	{
		if (i != idx)
			new_env[j++] = ft_strdup(env[i]);
		i++;
	}
	new_env[j] = NULL;
	*envp_ptr = new_env;
}

int	my_unset(char **args, char ***envp_ptr)
{
	int	i;
	int	idx;

	i = 1;
	while (args[i])
	{
		if (is_valid_identifier(args[i]))
		{
			idx = env_var_index(args[i], *envp_ptr);
			if (idx != -1)
				remove_env_var(idx, envp_ptr);
		}
<<<<<<< HEAD
		i++;
	}
	my_getenv(NULL, *envp_ptr);
=======
		else
		{
			ft_putstr_fd("unset: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("`: not a valid identifier\n", 2);
		}
		i++;
	}
>>>>>>> dahani
	return (0);
}
