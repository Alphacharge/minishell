/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 10:52:36 by rbetz             #+#    #+#             */
/*   Updated: 2022/11/23 11:42:52 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include "libft.h"
#include "utils.h"

/*deletes all given vars from env if they exist, returns NULL if env is empty or env*/
t_env	*unset(int argc, char **argv, t_env *env)
{
	t_env	*head;
	t_env	*prev;
	int		i;

	head = env;
	i = 1;
	if (argc == 1)
		return (ft_putstr_fd("unset: not enough arguments", 2), head);
	if (env == NULL)
		return (NULL);
	while (i < argc && env != NULL && env->name != NULL && argv[i] != NULL && !ft_strcmp(argv[i], env->name))
	{
		head = env->next;
		env->next = NULL;
		delete_env(env);
		env = head;
		i++;
	}
	prev = head;
	if (env != NULL)
		env = env->next;
	while (i < argc && env != NULL && env->name != NULL && argv[i] != NULL)
	{
		if (ft_strcmp(argv[i], env->name))
		{
			prev = env;
			env = env->next;
		}
		else
		{
			prev->next = env->next;
			env->next = NULL;
			delete_env(env);
		}
		i++;
	}
	print_env(head, 1);
	return (head);
}

/*accepts var to unset in env*/
// t_env	*unset(char *var, t_env *env)
// {
// 	t_env	*head;
// 	t_env	*tmp;

// 	head = env;
// 	if (var == NULL || env == NULL)
// 		return (NULL);
// 	if (!ft_strcmp(var, env->name))
// 	{
// 		head = env->next;
// 		ft_free(env);
// 	}
// 	else
// 	{
// 		tmp = env;
// 		env = env->next;
// 		while (env != NULL)
// 		{
// 			if (!ft_strcmp(var, env->name))
// 			{
// 				tmp->next = env->next;
// 				ft_free(env);
// 				break ;
// 			}
// 			tmp = env;
// 			env = env->next;
// 		}
// 	}
// 	return (head);
// }
