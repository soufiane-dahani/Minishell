/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 10:08:18 by yaait-am          #+#    #+#             */
/*   Updated: 2025/04/29 18:59:10 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handler_interactive(int sig)
{
	if (!g_ast->sign)
	if (sig == SIGINT)
	{
		g_ast->exit_status = 130;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handler_execution(int sig)
{
	if (sig == SIGINT)
	{
		sig = 1;
		g_ast->exit_status = 130;
		write(1, "\n", 1);
	}
	else if (sig == SIGQUIT)
	{
		g_ast->exit_status = 131;
		write(2, "Quit (core dumped)\n", 19);
		sig = 1;
	}
}

void	setup_execution_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = handler_execution;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

void	reset_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	setup_interactive_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = handler_interactive;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}
