/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arraycount.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 14:53:27 by fkernbac          #+#    #+#             */
/*   Updated: 2022/11/23 11:28:56 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/*Returns argc value for argv.*/
int	arraycount(char **array)
{
	int	i;

	i = 0;
	if (array == NULL)
		return (0);
	while (array[i] != NULL)
		i++;
	return (i);
}
