/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 17:31:50 by rbetz             #+#    #+#             */
/*   Updated: 2022/12/23 17:48:26 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	is_valid_var(char *var)
{
	int	i;

	i = 0;
	if (var == NULL)
		return (0);
	if (var[i] != '\0' && var[i] != '_' && !ft_isalpha(var[i]))
		return (0);
	while (var[i] != '\0' && (ft_isalnum(var[i]) || var[i] == '_'))
		i++;
	if (var[i] == '\0')
		return (1);
	return (0);
}
