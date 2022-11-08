/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorhandling.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 09:29:26 by rbetz             #+#    #+#             */
/*   Updated: 2022/11/08 17:16:48 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORHANDLING_H
# define ERRORHANDLING_H

# include "structs.h"
# include <stdlib.h>
# include <stdio.h>

void	ft_error(char *message);
void	clean(t_var *var);

#endif
