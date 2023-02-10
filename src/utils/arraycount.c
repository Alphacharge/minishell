/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arraycount.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 14:53:27 by fkernbac          #+#    #+#             */
/*   Updated: 2023/02/10 14:22:40 by rbetz            ###   ########.fr       */
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
