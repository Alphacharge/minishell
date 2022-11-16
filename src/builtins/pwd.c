/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 10:32:18 by rbetz             #+#    #+#             */
/*   Updated: 2022/11/16 11:57:06 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

void	pwd(int argc, char **argv)
{
	char	*dir;

	if (argc != 1)
	{
		write(2, "pwd: bad option: ", 17);
		if (argv[1] != NULL)
			write(2, argv[1], ft_strlen(argv[1]));
		write(2, '\n', 1);
	}
	else
	{
		dir = getcwd(NULL, 0);
		if (dir == NULL)
			write(1, '\n', 1);
		else
		{
			ft_putendl_fd(dir, 1);
			free(dir);
		}
	}
}
