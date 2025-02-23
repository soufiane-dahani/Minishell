/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 09:32:09 by yaait-am          #+#    #+#             */
/*   Updated: 2025/02/23 11:09:24 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing(char *s)
{
	if (s == NULL || !ft_strncmp(s, "exit", 5))
	{
		printf("exit\n");
		free(s);
		exit(0);
	}
	else if (s[0] != 0)
	{
		add_history(s);
		printf("bash: %s: command not found\n", s);
	}
}

int	main(int ac, char **av)
{
	char	*s;

	(void)av;
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	if (ac != 1)
	{
		printf("\n [ ==> Usage: ./minishell <== ]\n\n");
		return (1);
	}
	while (1)
	{
		s = readline("minishell$> ");
		parsing(s);
		free(s);
	}
}
