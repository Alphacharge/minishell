/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorhandling.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 09:29:26 by rbetz             #+#    #+#             */
/*   Updated: 2022/10/28 14:27:59 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORHANDLING_H
# define ERRORHANDLING_H

# include "structs.h"
# include <stdlib.h>
# include <stdio.h>

void	ft_error(t_var *var, int code);
void	clean(t_var *var);

#endif