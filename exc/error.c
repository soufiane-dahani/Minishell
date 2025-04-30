/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:26:37 by sodahani          #+#    #+#             */
/*   Updated: 2025/04/29 19:24:56 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			level = ft_atoi((*env)[i] + 6);
			level++;
			g_ast->shell = level;
			new_val = ft_itoa(level);
			tmp = ft_strjoin("SHLVL=", new_val);
			(*env)[i] = tmp;
			return ;
		}
		i++;
	}
}

int	exit_status(int status)
{
	if (WIFEXITED(status))
		g_ast->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_ast->exit_status = 128 + WTERMSIG(status);
	else if (WIFSTOPPED(status))
		g_ast->exit_status = 128 + WSTOPSIG(status);
	return (g_ast->exit_status);
}
