/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 10:52:27 by rbetz             #+#    #+#             */
/*   Updated: 2022/11/23 16:31:18 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include "libft.h"

static void	export_print(t_env *env)
{
	while (env != NULL)
	{
		write(1, "declare -x ", 11);
		write(1, env->name, ft_strlen(env->name));
		write(1, "=\"", 2);
		write(1, env->value, ft_strlen(env->value));
		write(1, "\"\n", 2);
	}
}

static t_env	*update_values(int argc, char **argv, t_env *env)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		//check 4 values to update
	}
}

t_env	*export(int argc, char **argv, t_env *env)
{
	t_env	*head;
	t_env	*new;
	int		i;
	
	head = env;
	i = 1;
	if (argc == 1)
		export_print(env);
	head = update_values(argc, argv, env);
	while (i < argc)
	{
		new = new_env();
		if (new == NULL)
			return (head);
		new->name = ft_first_word(argv[i], '=', 0);
		new->value = ft_first_word(argv[i], '=', 1);
		new->next = env;
		head = new;
		i++;
	}
	return (head);
}

/*accepts name and value for new var in env and returns env*/
/*returns env if value or name are empty, nothing changed*/
/*returns NUll if env is empty and malloc fails*/
// t_env	*export(char *name, char *value, t_env *env)
// {
// 	t_env	*head;
// 	t_env	*new;

// 	head = env;
// 	if (name == NULL || value == NULL)
// 		return (env);
// 	if (head == NULL)
// 	{
// 		head = new_env();
// 		if (head == NULL)
// 			return (NULL);
// 		head->name = name;
// 		head->value = value;
// 		return (head);
// 	}
// 	else
// 	{
// 		new = new_env();
// 		if (new == NULL)
// 			return (head);
// 		while (env != NULL && env->next != NULL)
// 			env = env->next;
// 		if (env != NULL)
// 			env->next = new;
// 		return (head);
// 	}
// }
