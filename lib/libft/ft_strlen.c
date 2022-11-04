/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 14:06:12 by pnolte            #+#    #+#             */
/*   Updated: 2022/11/04 13:06:06 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlen(const char *c)
{
	int	index;

	index = 0;
	if (c == NULL)
		return (0);
	while (c[index] != '\0')
		index++;
	return (index);
}

// int	main(void)
// {
// 	char	a[] = "Program";
// 	char	b[] = {'P', 'r', 'o', 'g', 'r', 'a', 'm', '\0'};

// 	printf("Length of string a = %lu \n", strlen(a));
// 	printf("Length of string a = %d \n", ft_strlen(a));
// 	printf("Length of string b = %lu \n", strlen(b));
// 	printf("Length of string b = %d \n", ft_strlen(b));
// }
