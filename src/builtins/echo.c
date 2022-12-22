/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:04:50 by rbetz             #+#    #+#             */
/*   Updated: 2022/12/21 11:50:29 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

/*Will ignore option -n if it is not the first parameter. Prints every argument
to standard output, separated by a space.*/
void	echo(char **argv)
{
	int	i;

	i = 1;
	while (argv[i] != NULL && ft_strcmp(argv[i], "-n") == 0)
		i++;
	while (argv[i] != NULL)
	{
		ft_putstr_fd(argv[i], 1);
		i++;
		if (argv[i] != NULL)
			write(1, " ", 1);
	}
	if (ft_strcmp(argv[1], "-n") != 0)
		write(1, "\n", 1);
}
