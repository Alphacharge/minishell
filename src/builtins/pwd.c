/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 10:32:18 by rbetz             #+#    #+#             */
/*   Updated: 2023/02/08 13:28:06 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*accepts no args*/
int	pwd(void)
{
	char	*dir;

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
