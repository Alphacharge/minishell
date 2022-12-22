/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 10:52:33 by rbetz             #+#    #+#             */
/*   Updated: 2022/12/21 10:41:58 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

//The exit utility shall cause the shell to exit from its current
//execution environment with the exit status specified by the
//unsigned decimal integer n.  If the current execution environment
//is a subshell environment, the shell shall exit from the subshell
//environment with the specified exit status and continue in the
//environment from which that subshell environment was invoked;
//otherwise, the shell utility shall terminate with the specified
//exit status. If n is specified, but its value is not between 0
//and 255 inclusively, the exit status is undefined.
int	shell_exit(char **argv)
{
	int	status;

	if (argv && argv[1] != NULL && argv[2] != NULL)
		return (ft_error(NULL, "exit", "too many arguments"), EXIT_FAILURE);
	write(1, "exit\n", 5);
	if (argv == NULL || argv[1] == NULL)
		return (EXIT_SUCCESS);
	status = ft_atoi(argv[1]);
	if (status > 255 || status < 0)
		return (EXIT_FAILURE);
	return (status);
}
