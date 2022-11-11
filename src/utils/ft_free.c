/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 20:57:09 by fkernbac          #+#    #+#             */
/*   Updated: 2022/11/07 21:45:23 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

//Frees memory of n arguments if they are not pointing to NULL.
void	free_multiple(int n, ...)
{
	va_list	args;
	void	*pointer;

	pointer = NULL;
	if (n <= 0)
		return ;
	va_start(args, n);
	while (n > 0)
	{
		pointer = va_arg(args, void *);
		if (pointer != NULL)
			free(pointer);
		n--;
	}
	va_end(args);
}

//Frees pointer and returns NULL.
void	*ft_free(void *pointer)
{
	if (pointer != NULL)
		free(pointer);
	return (NULL);
}
