/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 09:44:03 by rbetz             #+#    #+#             */
/*   Updated: 2023/02/10 14:22:40 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*returns a pointer to the value of a env variable*/
char	*get_env_var(t_env *env, char *name)
{
	while (env != NULL)
	{
		if (ft_strcmp(name, env->name) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

/*sets a variable to a new value, if the var not exist it returns NULL*/
t_env	*set_env_var(t_env *env, char *name, char *value)
{
	t_env	*head;

	head = env;
	if (env == NULL || name == NULL || value == NULL)
		return (head);
	while (env != NULL && ft_strcmp(env->name, name) != 0)
		env = env->next;
	if (env != NULL)
	{
		free_multiple(1, &env->value);
		env->value = value;
	}
	return (head);
}
