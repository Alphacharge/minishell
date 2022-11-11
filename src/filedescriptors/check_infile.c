/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_infile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 10:12:16 by rbetz             #+#    #+#             */
/*   Updated: 2022/11/07 21:14:19 by fkernbac         ###   ########.fr       */
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
		ft_error(var);
	}
	if (access(file, R_OK) < 0)
	{
		free(file);
		ft_error(var);
	}
	var->fd_in = open(file, O_RDONLY);
	free(file);
	if (var->fd_in < 0)
		ft_error(var);
}
