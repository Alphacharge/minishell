/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_outfile.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 10:12:16 by rbetz             #+#    #+#             */
/*   Updated: 2022/11/07 21:14:25 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filedescriptors.h"

void	check_outfile(t_var *var, int argc, char **argv)
{
	char	*file;

	if (ft_strchr(argv[argc - 1], '/') == 0)
		file = combine_pathprog(var->pwd, argv[argc - 1]);
	else
		file = ft_strdup(argv[argc - 1]);
	if (!var->here)
		var->fd_out = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
		var->fd_out = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	free(file);
	if (var->fd_out < 0)
		ft_error(var);
}
