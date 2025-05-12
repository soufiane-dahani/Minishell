/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 10:08:18 by yaait-am          #+#    #+#             */
/*   Updated: 2025/05/12 09:09:23 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handler_interactive(int sig)
{
	if (sig == SIGINT)
	{
		g_exit = 130;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	reset_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	setup_interactive_signals(void)
{
	signal(SIGINT, handler_interactive);
	signal(SIGQUIT, SIG_IGN);
}

void	handle_signal_for_herdoc(int sig)
{
	if (sig == SIGINT)
	{
		g_exit = 130;
		write(1, "\n", 1);
		close(0);
	}
}
