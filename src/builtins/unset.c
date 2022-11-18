/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 10:52:36 by rbetz             #+#    #+#             */
/*   Updated: 2022/11/18 15:14:35 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include "libft.h"

/*accepts var to unset in env*/
t_env	*unset(char *var, t_env *env)
{
	t_env	*head;
	t_env	*tmp;
	int		len;
	
	if (var == NULL || env == NULL)
		return (NULL);
	len = ft_strlen(var);
	if (!ft_strncmp(var, env->name, len))
		head = env->next;
	else
	{
		tmp = env;
		env = env->next;
		while (env != NULL)
		{
			if (!ft_strncmp(var, env->name, len))
			{
				tmp->next = env->next;
				free(env);
				break ;
			}
			tmp = env;
			env = env->next;
		}
	}
}