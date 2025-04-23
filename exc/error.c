/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:26:37 by sodahani          #+#    #+#             */
/*   Updated: 2025/04/23 16:27:44 by sodahani         ###   ########.fr       */
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
