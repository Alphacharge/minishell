/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:04:50 by rbetz             #+#    #+#             */
/*   Updated: 2022/12/24 12:55:54 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

/*Will ignore option -n if it is not the first parameter. Prints every argument
to standard output, separated by a space.*/
int	echo(char **argv)
{
	int		i;
	int		n;
	char	*s;

	i = 1;
	n = false;
	while (argv[i] != NULL && ft_strncmp(argv[i], "-n", 2) == 0)
	{
		s = argv[i] + 2;
		while (*s == 'n')
			s++;
		if (*s == 0)
			n = true;
		else
			break ;
		i++;
	}
	if (n == false)
		i = 1;
	while (argv[i] != NULL)
	{
		ft_putstr_fd(argv[i], 1);
		i++;
		if (argv[i] != NULL)
			write(1, " ", 1);
	}
	if (n == false)
		write(1, "\n", 1);
	return (0);
}
