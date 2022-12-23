/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 10:52:33 by rbetz             #+#    #+#             */
/*   Updated: 2022/12/23 13:17:49 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

/*Prints exit and returns exit status of given argument.*/
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
