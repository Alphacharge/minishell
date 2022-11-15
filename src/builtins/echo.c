/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:04:50 by rbetz             #+#    #+#             */
/*   Updated: 2022/11/15 14:11:43 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"
#include <stdio.h>

void	echo(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc < 1)
		printf("\n");
	else if (ft_strncmp(argv[i], "-n", 2) == 0)
}