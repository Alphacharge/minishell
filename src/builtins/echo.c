/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:04:50 by rbetz             #+#    #+#             */
/*   Updated: 2023/02/13 13:58:47 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print(char **argv, int i)
{
	ft_putstr_fd(argv[i], 1);
	i++;
	if (argv[i] != NULL)
		write(1, " ", 1);
	return (i);
}

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
		i = print(argv, i);
	if (n == false)
		write(1, "\n", 1);
	return (0);
}
