/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorhandling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 09:29:07 by rbetz             #+#    #+#             */
/*   Updated: 2022/11/11 16:25:44 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errorhandling.h"

/*Prints error message and returns 1.*/
int	ft_error(char *message)
{
//PLACEHOLDER: pattern for error messages
	if (message == NULL)
		perror("program:sourcefile ");
	else
		perror(message);
	return (EXIT_FAILURE);
}
