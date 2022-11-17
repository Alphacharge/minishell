/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:42:42 by fkernbac          #+#    #+#             */
/*   Updated: 2022/11/15 17:16:33 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/*Checks for shell tokens but not for quotation marks.*/
int	is_token(char c)
{
	if (c == '|' || c == '<' || c == '>' || c == '$')
		return (1);
	return (0);
}
