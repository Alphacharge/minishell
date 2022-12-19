/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorhandling.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humbi <humbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 09:29:26 by rbetz             #+#    #+#             */
/*   Updated: 2022/12/19 14:15:06 by humbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORHANDLING_H
# define ERRORHANDLING_H

# include <stdlib.h>
# include <stdio.h>
# include "libft.h"

int		ft_error(char *function, char *filename, char *message);

#endif
