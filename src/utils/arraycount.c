/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arraycount.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humbi <humbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 14:53:27 by fkernbac          #+#    #+#             */
/*   Updated: 2023/01/28 14:54:11 by humbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
