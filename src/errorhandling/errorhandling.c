/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorhandling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 09:29:07 by rbetz             #+#    #+#             */
/*   Updated: 2022/12/02 19:59:46 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errorhandling.h"

/*Prints error message and returns 1.*/
int	ft_error(char *filename)
{
	char	*message;

	if (filename == NULL)
		return (perror("Minishell"), EXIT_FAILURE);
	message = ft_strjoin("Minishell: ", filename);
	perror(message);
	free(message);
	return (EXIT_FAILURE);
}
