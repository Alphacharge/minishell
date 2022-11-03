/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multijoin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 16:08:04 by rbetz             #+#    #+#             */
/*   Updated: 2022/11/03 12:34:01 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static char	*alloc(int n, char **arr)
{
	int		i;
	int		len;
	char	*str;

	i = 0;
	len = 0;
	str = NULL;
	while (i < n)
		len += ft_strlen(arr[i++]);
	str = ft_calloc((len + 1), sizeof(char));
	if (str == NULL)
		return (NULL);
	return (str);
}

static void	read_args(char **input, va_list args, int n)
{
	int	i;

	i = 0;
	while (i < n)
		input[i++] = va_arg(args, char *);
	va_end(args);
}

//accepts up to 64 strings to join together
char	*multijoin(bool tofr, int n, ...)
{
	va_list	args;
	char	*str;
	char	*input[64];
	int		i;
	size_t	length;
	length = 0;
	if (n < 2 || n >= 64)
		return (NULL);
	va_start(args, n);
	//segv
	read_args(input, args, n);
	str = alloc(n, input);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		ft_memcpy(&str[length], &input[i], ft_strlen(input[i]));
		length += ft_strlen(input[i++]);
	}
	i = 0;
	while (tofr == true && i < n)
		free(input[i++]);
	return (str);
}
