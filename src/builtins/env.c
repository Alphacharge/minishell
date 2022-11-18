/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 10:48:08 by rbetz             #+#    #+#             */
/*   Updated: 2022/11/18 10:21:19 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include "libft.h"

/*accepts no args, prints env*/
void	env(int argc, char **argv, t_env *env)
{
	if (argc != 1)
	{
		write(2, "env: illegal option ", 20);
		if (argv[1] != NULL)
			write(2, argv[1], ft_strlen(argv[1]));
		write(2, "\n", 1);
	}
	else
		print_env(env, 1);
}
