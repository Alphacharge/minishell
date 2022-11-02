/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multijoin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 16:08:04 by rbetz             #+#    #+#             */
/*   Updated: 2022/11/02 16:29:44 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*multijoin(int n, bool tofr, ...)
{
	va_list	args;
	int		length;
	int		i;
	char	*str;
	int pos;

	length = 0;
	i = 0;
	str = NULL;
	va_start(args, tofr);
	while (i < n)
		length += ft_strlen(args[i++]);
	str = ft_calloc((length + 1), sizeof(char));
	if (str == NULL)
		return (NULL);
	i = 0;
	pos = 0;
	while (i < n)
	{
		length = ft_strlen(args[i]);
		ft_memcpy(str[pos], args[i++], length);
		pos += length;
	}
	va_end(args);
	return (str);
}
