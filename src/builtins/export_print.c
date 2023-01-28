/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humbi <humbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 10:44:40 by rbetz             #+#    #+#             */
/*   Updated: 2023/01/28 14:52:36 by humbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_print(t_env *env)
{
	while (env != NULL)
	{
		write(1, "declare -x ", 11);
		write(1, env->name, ft_strlen(env->name));
		if (env->value != NULL)
		{
			write(1, "=\"", 2);
			write(1, env->value, ft_strlen(env->value));
		}
		write(1, "\"\n", 2);
		env = env->next;
	}
}
