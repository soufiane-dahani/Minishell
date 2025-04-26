/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:26:37 by sodahani          #+#    #+#             */
/*   Updated: 2025/04/26 14:44:03 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_error(char *message)
{
	int	i;

	i = 0;
	write(2, ANSI_COLOR_RED, 5);
	while (message[i])
		i++;
	write(2, message, i);
	write(2, ANSI_RESET_ALL, 4);
}

char	**add_new_env_if_not_found(void)
{
	char	**env;
	int		len;
	char	cwd[1024];
	char	*pwd;

	env = ft_malloc(sizeof(char *) * 4, FT_ALLOC);
	if (!env)
		return (NULL);
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (NULL);
	pwd = ft_malloc(ft_strlen("PWD=") + ft_strlen(cwd) + 1, FT_ALLOC);
	len = ft_strlen("PWD=") + ft_strlen(cwd) + 1;
	if (!pwd)
		return (NULL);
	ft_strcpy(pwd, "PWD=");
	ft_strlcat(pwd, cwd, len);
	env[0] = pwd;
	env[1] = ft_strdup("SHLVL=1");
	env[2] = ft_strdup("_=/usr/bin/env");
	env[3] = NULL;
	return (env);
}

void	add_shlvl(char ***env)
{
	int		i;
	int		level;
	char	*new_val;
	char	*tmp;

	i = 0;
	while ((*env)[i])
	{
		if (ft_strncmp((*env)[i], "SHLVL=", 6) == 0)
		{
			level = atoi((*env)[i] + 6);
			level++;
			new_val = ft_itoa(level);
			tmp = ft_strjoin("SHLVL=", new_val);
			free(new_val);
			free((*env)[i]);
			(*env)[i] = tmp;
			return ;
		}
		i++;
	}
	tmp = ft_strdup("SHLVL=1");
}
