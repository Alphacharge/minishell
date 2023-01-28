/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humbi <humbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 10:48:08 by rbetz             #+#    #+#             */
/*   Updated: 2023/01/28 14:52:29 by humbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*accepts no args, prints env*/
int	env(char **argv, t_env *env)
{
	if (argv[0] == NULL || argv[1] != NULL)
		return (ft_error("minishell: env", NULL, 5));
	print_env(env, 1);
	return (0);
}
