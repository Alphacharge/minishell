/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_infile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 10:12:16 by rbetz             #+#    #+#             */
/*   Updated: 2022/10/28 14:32:42 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filedescriptors.h"

void	check_infile(t_var *var, char **argv)
{
	char	*file;

	if (ft_strchr(argv[1], '/') == 0)
		file = combine_pathprog(var->pwd, argv[1]);
	else
		file = ft_strdup(argv[1]);
	if (access(file, F_OK) < 0)
	{
		free(file);
		ft_error(var, 3);
	}
	if (access(file, R_OK) < 0)
	{
		free(file);
		ft_error(var, 6);
	}
	var->fd_in = open(file, O_RDONLY);
	free(file);
	if (var->fd_in < 0)
		ft_error(var, 7);
}
