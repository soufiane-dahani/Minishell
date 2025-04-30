/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 10:08:18 by yaait-am          #+#    #+#             */
/*   Updated: 2025/04/30 08:33:52 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void handler_interactive(int sig)
{
	g_ast->exit_status = 130;
	if (sig == SIGINT)
	{
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

void	reset_signals(void)
{
	signal(SIGINT, handler_execution);
	signal(SIGQUIT, handler_execution);
}

void setup_interactive_signals(void)
{
	signal(SIGINT, handler_interactive);
	signal(SIGQUIT, SIG_IGN);
}
