/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combine_pathprog.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humbi <humbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 17:26:06 by rbetz             #+#    #+#             */
/*   Updated: 2023/01/28 14:54:15 by humbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Allocates a new string with path + / + programm*/
char	*combine_pathprog(char *path, char *prog)
{
	int		pale;
	int		pole;
	int		i;
	int		j;
	char	*ret;

	if (path == NULL || prog == NULL)
		return (ft_strdup("./"));
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
