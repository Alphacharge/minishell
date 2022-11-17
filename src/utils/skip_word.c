/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:36:51 by fkernbac          #+#    #+#             */
/*   Updated: 2022/11/15 19:38:00 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	is_word(char c)
{
	if (c != '\0' && ft_isspace(c) == 0 && is_token(c) == 0)
		return (1);
	return (0);
}

/*Skips characters until it encounters whitespace or token.*/
char	*skip_word(char *s)
{
	int	i;

	i = 0;
	while (is_word(s[i]) == 1)
		i++;
	return (s + i);
}
