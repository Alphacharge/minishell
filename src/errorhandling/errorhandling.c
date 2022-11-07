/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorhandling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 09:29:07 by rbetz             #+#    #+#             */
/*   Updated: 2022/11/07 20:53:32 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errorhandling.h"

void	ft_error(t_var *var)
{
	perror("program:sourcefile ");
	clean(var);
	exit(EXIT_FAILURE);
}
