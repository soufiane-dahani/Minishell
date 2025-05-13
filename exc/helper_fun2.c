/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_fun2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:26:37 by sodahani          #+#    #+#             */
/*   Updated: 2025/05/12 07:15:59 by yaait-am         ###   ########.fr       */
=======
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:26:37 by sodahani          #+#    #+#             */
/*   Updated: 2025/04/26 14:39:42 by sodahani         ###   ########.fr       */
>>>>>>> dahani
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env_size(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

void	swap_strs(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	sort_env(char **env)
{
	int	size;
	int	j;
	int	i;

	size = ft_env_size(env);
	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (ft_strcmp(env[j], env[j + 1]) > 0)
				swap_strs(&env[j], &env[j + 1]);
			j++;
		}
		i++;
	}
}

int	open_file(char *filename, int mode)
{
	int	fd;

<<<<<<< HEAD
	if (mode == TYP_REDAPP)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (mode == TYP_REDOUT)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (mode == TYP_REDIN)
=======
	if (mode == 0)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (mode == 1)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (mode == 2)
>>>>>>> dahani
		fd = open(filename, O_RDONLY);
	else
		return (-1);
	return (fd);
}
<<<<<<< HEAD

char	**handle_exp_for_camond(char **cmd)
{
	int	i;

	i = 0;
	cmd = handle_wildcards_for_string(cmd);
	while (cmd[i])
	{
		if (is_couple(cmd[i]) || is_single(cmd[i]))
			cmd[i] = exp_for_herdoc(cmd[i]);
		if (!is_has_quote(cmd[i]))
		{
			cmd[i] = exp_for_herdoc(cmd[i]);
			cmd = split_the_no_quoted(cmd, &i);
		}
		else
			cmd[i] = before_quote(cmd[i]);
		cmd[i] = skip_quote(cmd[i]);
		i++;
	}
	return (cmd);
}
=======
>>>>>>> dahani
