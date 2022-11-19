/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 10:52:33 by rbetz             #+#    #+#             */
/*   Updated: 2022/11/19 11:36:59 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

    //    The exit utility shall cause the shell to exit from its current
    //    execution environment with the exit status specified by the
    //    unsigned decimal integer n.  If the current execution environment
    //    is a subshell environment, the shell shall exit from the subshell
    //    environment with the specified exit status and continue in the
    //    environment from which that subshell environment was invoked;
    //    otherwise, the shell utility shall terminate with the specified
    //    exit status. If n is specified, but its value is not between 0
    //    and 255 inclusively, the exit status is undefined.
int	shell_exit(char **argv)
{
	int	status;

	if (argv[1] == NULL)
		return (EXIT_SUCCESS);
	else if (argv[2] != NULL)
		return (write(1, "minishell: exit: too many arguments\n", 37), -1);
	status = ft_atoi(argv[1]);
	if (status > 255 || status < 0)
		return (EXIT_FAILURE);
	return (status);
}
