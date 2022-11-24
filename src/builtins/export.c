/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 10:52:27 by rbetz             #+#    #+#             */
/*   Updated: 2022/11/24 16:18:15 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include "libft.h"
#include <stdio.h>
static void	export_print(t_env *env)
{
	while (env != NULL)
	{
		write(1, "declare -x ", 11);
		write(1, env->name, ft_strlen(env->name));
		if (env->value != NULL)
		{
			write(1, "=\"", 2);
			write(1, env->value, ft_strlen(env->value));
		}
		write(1, "\"\n", 2);
		env = env->next;
	}
}

static t_env	*update_values(int argc, char **argv, t_env *env)
{
	t_env	*ret;
	char	*name;
	char	*value;
	int		i;

	i = 1;
	while (i < argc)
	{
		if (argv[i] != NULL)
		{
			name = ft_first_word(argv[i], '=', 0);
			value = ft_first_word(argv[i], '=', 1);
			// printf("%s\n", value);
			ret = set_env_var(env, name, value);
			if (ret == NULL)
				free_multiple(1, &value);
			else
				env = ret;
			if (name != NULL)
				free_multiple(1, &name);
		}
		i++;
	}
	return (env);
}

t_env	*export(int argc, char **argv, t_env *env)
{
	t_env	*head;
	t_env	*new;
	char	*name;
	int		i;
	
	head = env;
	i = 1;
	if (argc == 1)
		export_print(env);
	head = update_values(argc, argv, env);
	while (i < argc)
	{
		env = head;
				// printf("$$%s,%s\n", head->name, head->value);
		if (argv[i] != NULL)
		{
			name = ft_first_word(argv[i], '=', 0);
			printf(">>%s\n", name);
			if (get_env_var(env, name) == NULL)
			{
				new = new_env();
				if (new == NULL)
					return (free_multiple(1, &name), head);
				new->name = name;
				new->value = ft_first_word(argv[i], '=', 1);
				new->next = env;
				head = new;
				// printf("%s,%s\n", head->name, head->value);
				// printf("%s,%s\n", env->name, env->value);
				// printf("%s,%s\n", new->name, new->value);
			}
			else
				free_multiple(1, &name);
		}
		i++;
	}
				// printf("$$%s,%s\n", head->name, head->value);
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
