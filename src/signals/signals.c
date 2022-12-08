/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 13:04:15 by fkernbac          #+#    #+#             */
/*   Updated: 2022/12/08 09:58:41 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

//key inputs are still displayed
void	signal_handler(int signum)
{
	if (signum == SIGQUIT)
	{
		rl_replace_line("", 0);
		rl_redisplay();
		return ;
	}
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		return ;
	}
}

/*ctrl + c: SIGINT*/
/*ctrl + d: end of transmission (4)*/
void	set_signals(void)
{
	struct sigaction	sig_actions;

	sig_actions.sa_handler = signal_handler;
	sig_actions.sa_flags = 0;
	sigemptyset(&sig_actions.sa_mask);
	sigaddset(&sig_actions.sa_mask, SIGINT);
	// sigaddset(&sig_actions.sa_mask, SIGQUIT);
	sigaction(SIGINT, &sig_actions, NULL);
	sigaction(SIGQUIT, &sig_actions, NULL);
}
