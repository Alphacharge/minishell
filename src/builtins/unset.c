/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 10:52:36 by rbetz             #+#    #+#             */
/*   Updated: 2022/12/21 11:51:14 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

/*deletes all given vars from env if they exist,*/
/*returns NULL if env is empty or env*/
t_env	*unset(char **argv, t_env *env)
{
	t_env	*head;
	t_env	*prev;
	int		i;

	head = env;
	prev = head;
	i = 1;
	if (argv[1] == NULL)
		return (ft_error(NULL, "unset", "not enough arguments"), head);
	if (env == NULL)
		return (NULL);
	while (argv[i] != NULL)
	{
		env = head;
		while (env != NULL && env->name != NULL && argv[i] != NULL)
		{
			if (ft_strcmp(argv[i], env->name))
			{
				prev = env;
				env = env->next;
			}
			else
			{
				if (env == head)
				{
					head = env->next;
					prev = head;
				}
				else
					prev->next = env->next;
				env->next = NULL;
				delete_env(env);
				i++;
				env = NULL;
			}
		}
	}
	return (head);
}
