/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 10:52:33 by rbetz             #+#    #+#             */
/*   Updated: 2023/02/04 15:26:16 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Checks if s is a valid numerical argument.*/
static int	is_num(char *s)
{
	s = skip_space(s);
	if ((*s == '-' || *s == '+') && *(s + 1) != 0)
		s++;
	while (*s != '\0')
	{
		if (*s < '0' || *s > '9')
			return (0);
		s++;
	}
	return (1);
}

/*Prints exit and returns exit status of given argument.*/
int	shell_exit(char **argv)
{
	int	status;

	status = EXIT_SUCCESS;
	if (argv == NULL)
		return (EXIT_FAILURE);
	if (argv[1] == NULL)
		write(1, "exit\n", 5);
	else
	{
		write(2, "exit\n", 5);
		status = EXIT_FAILURE;
		if (argv[1][0] == 0 || is_num(argv[1]) != 1)
			status = ft_error("minishell: exit", argv[1], 128);
		else if (argv[2] != NULL)
			status = ft_error("minishell: exit", NULL, 3);
		else
			status = ft_atoi(argv[1]);
		status = status % 256;
		if (status < 0)
			status += 256;
	}
	return (status);
}
