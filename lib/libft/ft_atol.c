/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 17:27:07 by rbetz             #+#    #+#             */
/*   Updated: 2022/11/15 14:49:38 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atol(char *str)
{
	long			vz;
	unsigned long	c;

	vz = 1;
	c = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '-')
	{
		str++;
		vz = -1;
	}
	else if (*str == '+')
		str++;
	if (!ft_strisdigit(str))
		return (0);
	while (ft_isdigit(*str))
	{
		c = c * 10 + *(str++) - '0';
		if (c > INT64_MAX && vz == -1)
			return (0);
		else if (c > (INT64_MAX - 1) && vz == 1)
			return (-1);
	}
	return ((long)(c * vz));
}
