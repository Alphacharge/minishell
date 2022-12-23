/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 10:48:08 by rbetz             #+#    #+#             */
/*   Updated: 2022/12/23 13:16:58 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

/*accepts no args, prints env*/
int	env(char **argv, t_env *env)
{
	if (argv[0] == NULL || argv[1] != NULL)
		return (ft_error("minishell: env", NULL, "illegal option"));
	print_env(env, 1);
	return (0);
}
