/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 10:32:18 by rbetz             #+#    #+#             */
/*   Updated: 2022/12/21 11:50:58 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

/*accepts no args*/
int	pwd(char **argv)
{
	char	*dir;

	if (argv[1] != NULL)
		return (ft_error(NULL, "pwd", "too many arguments"), -1);
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
