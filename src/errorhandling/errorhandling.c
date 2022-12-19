/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorhandling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humbi <humbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 09:29:07 by rbetz             #+#    #+#             */
/*   Updated: 2022/12/19 13:57:48 by humbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errorhandling.h"

/*Prints Minishell/function:filename:message/strerror to stderr and returns 1.*/
int	ft_error(char *function, char *filename, char *message)
{
	if (function == NULL)
		ft_putstr_fd("minishell: ", 2);
	else
	{
		ft_putstr_fd(function, 2);
		ft_putstr_fd(": ", 2);
	}
	if (message != NULL)
	{
		ft_putstr_fd(filename, 2);
		if (filename != NULL)
			ft_putstr_fd(": ", 2);
		ft_putstr_fd(message, 2);
		ft_putstr_fd("\n", 2);
	}
	else
		perror(filename);
	return (EXIT_FAILURE);
}
