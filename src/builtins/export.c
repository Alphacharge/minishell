/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 10:52:27 by rbetz             #+#    #+#             */
/*   Updated: 2022/11/21 09:28:28 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include "libft.h"

/*accepts name and value for new var in env and returns env*/
/*returns env if value or name are empty, nothing changed*/
/*returns NUll if env is empty and malloc fails*/
t_env	*export(char *name, char *value, t_env *env)
{
	t_env	*head;
	t_env	*new;

	head = env;
	if (name == NULL || value == NULL)
		return (env);
	if (head == NULL)
	{
		head == new_env();
		if (head == NULL)
			return (NULL);
		head->name = name;
		head->value = value;
		return (head);
	}
	else
	{
		new = new_env();
		if (new == NULL)
			return (head);
		while (env != NULL && env->next != NULL)
			env = env->next;
		if (env != NULL)
			env->next = new;
		return (head);
	}
}
