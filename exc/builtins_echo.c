/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:26:37 by sodahani          #+#    #+#             */
/*   Updated: 2025/05/07 14:46:47 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		printf("%s ", cmd[i]);
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
