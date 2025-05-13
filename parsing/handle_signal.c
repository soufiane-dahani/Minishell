/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 10:08:18 by yaait-am          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/05/12 09:09:23 by yaait-am         ###   ########.fr       */
=======
/*   Updated: 2025/04/27 19:18:01 by yaait-am         ###   ########.fr       */
>>>>>>> dahani
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handler_interactive(int sig)
{
	if (sig == SIGINT)
	{
<<<<<<< HEAD
		g_exit = 130;
=======
		g_ast->exit_status = 130;
>>>>>>> dahani
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

<<<<<<< HEAD
=======
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

>>>>>>> dahani
void	reset_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	setup_interactive_signals(void)
{
<<<<<<< HEAD
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
=======
	struct sigaction	sa;

	sa.sa_handler = handler_interactive;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}
>>>>>>> dahani
