/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 10:57:38 by rbetz             #+#    #+#             */
/*   Updated: 2023/02/10 14:22:40 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*is printing env linklist to fd your choice*/
void	print_env(t_env *env, int fd)
{
	if (env == NULL)
		ft_error(NULL, NULL, 8);
	else
	{
		while (env != NULL)
		{
			if (env->name != NULL)
				ft_putstr_fd(env->name, fd);
			ft_putstr_fd("=", fd);
			if (env->value != NULL)
				ft_putstr_fd(env->value, fd);
			ft_putstr_fd("\n", fd);
			env = env->next;
		}
	}
}
