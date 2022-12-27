/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorhandling.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 09:29:26 by rbetz             #+#    #+#             */
/*   Updated: 2022/12/27 14:32:25 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORHANDLING_H
# define ERRORHANDLING_H

# include <stdlib.h>
# include <stdio.h>
# include "libft.h"

int		g_exit_status;
int		ft_error(char *function, char *filename, int error);

#endif
