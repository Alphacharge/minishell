/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 10:52:27 by rbetz             #+#    #+#             */
/*   Updated: 2022/11/25 09:53:44 by rbetz            ###   ########.fr       */
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
			}
			else
				free_multiple(1, &name);
		}
		i++;
	}
	return (head);
}
