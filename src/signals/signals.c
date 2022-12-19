/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humbi <humbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 13:04:15 by fkernbac          #+#    #+#             */
/*   Updated: 2022/12/19 13:40:48 by humbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

void	signal_ignore(int signum)
{
	if (signum == SIGQUIT)
		write(1, "Quit: 3", 7);
	write(1, "\n", 1);
}

//key inputs are still displayed
void	signal_redisplay(int signum)
{
	if (signum == SIGQUIT)
	{
		rl_replace_line("  ", 0);
		rl_on_new_line();
		rl_redisplay();
		// write(1, "\b", 1);
		// write(1, "\b", 1);
		// write(1, " ", 1);
		// write(1, " ", 1);
		// write(1, "\b", 1);
		// write(1, "\b", 1);
	}
	if (signum == SIGINT)
	{
		// write(1, "\b", 1);
		// write(1, "\b", 1);
		// write(1, " ", 1);
		// write(1, " ", 1);
		// write(1, "\b", 1);
		// write(1, "\b", 1);
		rl_replace_line("  ", 0);
		rl_on_new_line();
		rl_redisplay();
		write(1, "\n", 1);
		rl_replace_line("  ", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

/*Resets signal handler to default actions.*/
void	unset_signals(void)
{
	struct sigaction	dfl;

	ft_memset(&dfl, 0, sizeof(dfl));
	sigemptyset(&dfl.sa_mask);
	dfl.sa_handler = SIG_DFL;
	dfl.sa_flags = 0;
	if (sigaction(SIGINT, &dfl, NULL) < 0)
		ft_error(NULL, "unset_signals", NULL);
}

void	set_exec_signals(void)
{
	struct sigaction	action;

	ft_memset(&action, 0, sizeof(action));
	sigemptyset(&action.sa_mask);
	action.sa_handler = signal_ignore;
	action.sa_flags = 0;
	// sigaddset(&action.sa_mask, SIGINT);
	// sigaddset(&action.sa_mask, SIGQUIT);
	if (sigaction(SIGINT, &action, NULL) < 0 || sigaction(SIGQUIT, &action, NULL) < 0)
		ft_error(NULL, "set_exec_signals", NULL);
}

/*ctrl + c: SIGINT*/
/*ctrl + d: end of transmission (4)*/
void	set_rl_signals(void)
{
	struct sigaction	action;

	ft_memset(&action, 0, sizeof(action));
	sigemptyset(&action.sa_mask);
	action.sa_handler = signal_redisplay;
	action.sa_flags = 0;
	// sigaddset(&action.sa_mask, SIGINT);
	// sigaddset(&action.sa_mask, SIGQUIT);
	if (sigaction(SIGINT, &action, NULL) < 0 || sigaction(SIGQUIT, &action, NULL) < 0)
		ft_error(NULL, "set_rl_signals", NULL);
}
