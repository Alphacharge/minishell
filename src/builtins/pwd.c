/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 10:32:18 by rbetz             #+#    #+#             */
/*   Updated: 2022/12/27 13:22:10 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

/*accepts no args*/
int	pwd(char **argv)
{
	char	*dir;

	if (argv[1] != NULL)
		return (ft_error("minishell: pwd", NULL, 3));
	dir = getcwd(NULL, 0);
	if (dir == NULL)
		write(1, "\n", 1);
	else
	{
		ft_putendl_fd(dir, 1);
		ft_free(dir);
	}
	return (0);
}
