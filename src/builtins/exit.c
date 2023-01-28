/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humbi <humbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 10:52:33 by rbetz             #+#    #+#             */
/*   Updated: 2023/01/28 14:52:32 by humbi            ###   ########.fr       */
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

	if (argv && argv[1] != NULL && argv[2] != NULL)
		return (ft_error("minishell: exit", NULL, 128));
	write(1, "exit\n", 5);
	if (argv == NULL || argv[1] == NULL)
		return (EXIT_SUCCESS);
	if (is_num(argv[1]) != 1)
		return (ft_error("minishell: exit", argv[1], 128));
	status = ft_atoi(argv[1]);
	if (status > 255 || status < 0)
		return (EXIT_FAILURE);
	return (status);
}
