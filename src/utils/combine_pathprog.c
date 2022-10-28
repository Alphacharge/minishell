/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combine_pathprog.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 17:26:06 by rbetz             #+#    #+#             */
/*   Updated: 2022/10/28 13:17:04 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "utils.h"

char	*combine_pathprog(char *path, char *prog)
{
	int		pale;
	int		pole;
	int		i;
	int		j;
	char	*ret;

	pale = ft_strlen(path);
	pole = ft_strlen(prog);
	ret = ft_calloc(pale + pole + 2, sizeof(char));
	i = 0;
	j = 0;
	while (i < pale)
	{
		ret[i] = path[i];
		i++;
	}
	ret[i++] = '/';
	while (j < pole)
	{
		ret[i + j] = prog[j];
		j++;
	}
	return (ret);
}
