/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 10:52:36 by rbetz             #+#    #+#             */
/*   Updated: 2022/11/21 14:31:56 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include "libft.h"
#include "utils.h"

/*accepts var to unset in env*/
t_env	*unset(char *var, t_env *env)
{
	t_env	*head;
	t_env	*tmp;

	head = env;
	if (var == NULL || env == NULL)
		return (NULL);
	if (!ft_strcmp(var, env->name))
	{
		head = env->next;
		ft_free(env);
	}
	else
	{
		tmp = env;
		env = env->next;
		while (env != NULL)
		{
			if (!ft_strcmp(var, env->name))
			{
				tmp->next = env->next;
				ft_free(env);
				break ;
			}
			tmp = env;
			env = env->next;
		}
	}
	return (head);
}
