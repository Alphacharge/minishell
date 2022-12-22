/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 10:48:08 by rbetz             #+#    #+#             */
/*   Updated: 2022/12/21 11:50:41 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

/*accepts no args, prints env*/
void	env(char **argv, t_env *env)
{
	if (argv[0] == NULL || argv[1] != NULL)
		ft_error("minishell: env", NULL, "illegal option");
	else
		print_env(env, 1);
}
