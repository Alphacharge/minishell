/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 13:04:15 by fkernbac          #+#    #+#             */
/*   Updated: 2022/11/19 14:25:29 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

extern int	g_new;

void	sigint_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_new = 1;
		write(1, "\n", 1);
	}
}

//ctrl + c: SIGINT
//ctrl + d: end of transmission (4)
void	set_signals(void)
{
	struct sigaction	sigint_action;

	sigint_action.sa_handler = sigint_handler;
	sigint_action.sa_flags = 0;
	sigemptyset(&sigint_action.sa_mask);
	sigaddset(&sigint_action.sa_mask, SIGINT);
	sigaction(SIGINT, &sigint_action, NULL);
}
