/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 20:57:09 by fkernbac          #+#    #+#             */
/*   Updated: 2022/11/18 16:34:14 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/*Frees an array and every pointer inside.*/
void	*free_ptr_array(void **array)
{
	int	i;

	i = 0;
	if (array == NULL)
		return (NULL);
	while (array[i] != NULL)
		free(array[i++]);
	free(array);
	return (NULL);
}

/*Frees memory of n arguments if they are not pointing to NULL.
Pointers are only freed, but not NULL pointers.*/
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

/*Frees pointer and returns NULL.*/
void	*ft_free(void *pointer)
{
	if (pointer != NULL)
		free(pointer);
	return (NULL);
}
