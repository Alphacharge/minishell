/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorhandling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 09:29:07 by rbetz             #+#    #+#             */
/*   Updated: 2022/10/28 13:20:58 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errorhandling.h"

static char	*message(int code)
{
	if (code == 1)
		return ("Error allocating Memory!\n");
	else if (code == 2)
		return ("Wrong amount of Arguments!");
	else if (code == 3)
		return ("Can't read file. File does not exist.");
	else if (code == 4)
		return ("Outfile is not writable.");
	else if (code == 5)
		return ("No Environment.");
	else if (code == 6)
		return ("Can't read file. Permission denied.");
	else if (code == 7)
		return ("Error opening infile.");
	else if (code == 8)
		return ("Your called Program is not installed.");
	else if (code == 9)
		return ("Can't duplicate fds.");
	else
		return ("Unknown Error.");
}

void	ft_error(t_var *var, int code)
{
	char	*str;

	str = message(code);
	clean(var);
	if (code == 0)
		exit(EXIT_SUCCESS);
	else
		perror(str);
	exit(EXIT_FAILURE);
}
