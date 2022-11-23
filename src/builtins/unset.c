/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 10:52:36 by rbetz             #+#    #+#             */
/*   Updated: 2022/11/23 14:56:58 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include "libft.h"
#include "utils.h"

/*deletes all given vars from env if they exist,*/
/*returns NULL if env is empty or env*/
t_env	*unset(int argc, char **argv, t_env *env)
{
	t_env	*head;
	t_env	*prev;
	int		i;

	head = env;
	prev = head;
	i = 1;
	if (argc < 2)
		return (ft_putstr_fd("unset: not enough arguments", 2), head);
	if (env == NULL)
		return (NULL);
	while (i < argc)
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
