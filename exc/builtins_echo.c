/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:26:37 by sodahani          #+#    #+#             */
/*   Updated: 2025/05/11 15:18:50 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

int	my_echo(char **cmd)
{
	int	i;
	int	flag;

	flag = 0;
	i = 1;
	if (cmd[1] == NULL)
	{
		printf("\n");
		return (0);
	}
	if (cmd[1][0] == '-' && cmd[1][1] == 'n' && cmd[1][2] == '\0')
	{
		flag = 1;
		i = 2;
	}
	while (cmd[i] != NULL)
	{
		printf("%s", cmd[i]);
		if (cmd[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (flag == 0)
		printf("\n");
	return (0);
}

int	count_entries(void)
{
	DIR				*dir;
	struct dirent	*entry;
	int				count;

	count = 0;
	dir = opendir(".");
	if (!dir)
		return (0);
	entry = readdir(dir);
	while (entry)
	{
		count++;
		entry = readdir(dir);
	}
	closedir(dir);
	return (count);
}

void	child_process2(t_ast *node, char **envp)
{
	execute(node->cmd, envp);
	ft_malloc(0, FT_CLEAR);
	exit(1);
}

void	execute_with_path(char **cmd, char **envp)
{
	struct stat	sb;

	if (stat(cmd[0], &sb) == 0 && S_ISDIR(sb.st_mode))
	{
		ft_malloc(0, FT_CLEAR);
		ft_putstr_fd(": Is a directory\n", 2);
		exit(126);
	}
	else if (access(cmd[0], F_OK) == -1)
	{
		ft_malloc(0, FT_CLEAR);
		perror("error");
		exit(127);
	}
	else if (access(cmd[0], X_OK) == -1)
	{
		ft_malloc(0, FT_CLEAR);
		perror(cmd[0]);
		exit(126);
	}
	else if (execve(cmd[0], cmd, envp) == -1)
		exit_for_child();
}

int	has_wildcard_char(char *str)
{
	int	j;

	j = 0;
	while (str[j])
	{
		if (str[j] == '*')
			return (1);
		j++;
	}
	return (0);
}
