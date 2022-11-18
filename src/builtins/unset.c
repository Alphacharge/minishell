/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 10:52:36 by rbetz             #+#    #+#             */
/*   Updated: 2022/11/18 16:23:26 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include "libft.h"

/*accepts var to unset in env*/
t_env	*unset(char *var, t_env *env)
{
	t_env	*head;
	t_env	*tmp;

	if (var == NULL || env == NULL)
		return (NULL);
	if (!ft_strncmp(var, env->name))
		head = env->next;
	else
	{
		tmp = env;
		env = env->next;
		while (env != NULL)
		{
			if (!ft_strcmp(var, env->name))
			{
				tmp->next = env->next;
				free(env);
				break ;
			}
			tmp = env;
			env = env->next;
		}
	}
	return (head);
}
