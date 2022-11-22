/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arraycount.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 14:53:27 by fkernbac          #+#    #+#             */
/*   Updated: 2022/11/22 14:54:57 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/*Returns argc value for argv.*/
int	arraycount(char **array)
{
	int	i;

	i = 0;
	if (array == NULL)
		return (NULL);
	while (array[i] != NULL)
		i++;
	return (i);
}
