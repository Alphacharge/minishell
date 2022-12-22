/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multijoin_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 16:08:04 by rbetz             #+#    #+#             */
/*   Updated: 2022/12/22 10:50:52 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "libft.h"

static char	*copy_input(char **array, size_t len)
{
	char	*str;
	size_t	i;
	size_t	pos;

	str = ft_calloc(len + 1, sizeof(char));
	i = 0;
	pos = 0;
	while (str != NULL && array[i] != NULL)
	{
		len = ft_strlen(array[i]);
		ft_memcpy(&str[pos], array[i], len);
		pos += len;
		i++;
	}
	return (str);
}

static size_t	read_input(char **array)
{
	size_t	i;
	size_t	pos;

	i = 0;
	pos = 0;
	while (array[pos] != NULL)
		i += ft_strlen(array[pos]);
	return (i);
}

static void	*free_array(char **array)
{
	size_t	i;

	i = 0;
	while (array[i] != NULL)
	{
		array[i] = ft_free(array[i]);
		i++;
	}
	return (NULL);
}

/*tofr, frees the input if true, array needs a Nullpointer at the end,*/
/*if a substring is null, the joining ends there*/
char	*multijoin_array(bool tofr, char **array)
{
	size_t	len;
	char	*str;

	if (array == NULL)
		return (NULL);
	len = read_input(array);
	str = copy_input(array, len);
	if (tofr == true)
		array = free_array(array);
	return (str);
}
