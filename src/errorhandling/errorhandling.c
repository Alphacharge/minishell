/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorhandling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 09:29:07 by rbetz             #+#    #+#             */
/*   Updated: 2022/11/08 17:16:20 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errorhandling.h"

void	ft_error(char *message)
{
	if (message == NULL)
		perror("program:sourcefile ");
	else
		perror(message);
	exit(EXIT_FAILURE);
}
