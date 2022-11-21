/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:04:50 by rbetz             #+#    #+#             */
/*   Updated: 2022/11/18 16:24:26 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"
#include <stdio.h>

/*is printing all args, -n needs to be in first arg*/
void	echo(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc == 1)
		write(1, "\n", 1);
	else if (argc > 1 && ft_strcmp(argv[i], "-n") == 0)
	{
		while (i < argc)
		{
			write(1, &argv[i], ft_strlen(argv[i]));
			i++;
		}
	}
	else
	{
		while (i < argc)
		{
			write(1, &argv[i], ft_strlen(argv[i]));
			i++;
		}
		write(1, "\n", 1);
	}
}
//i think it will not work properly with -n, it will print -n
