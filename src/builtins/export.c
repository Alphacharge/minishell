/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 10:52:27 by rbetz             #+#    #+#             */
/*   Updated: 2022/12/23 14:33:35 by rbetz            ###   ########.fr       */
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

int	export(int argc, char **argv, t_data *data)
{
	t_env	*tmp;
	t_env	*new;
	char	*name;
	int		i;

	tmp = data->env;
	i = 1;
	if (argc == 1)
		export_print(tmp);
	tmp = update_values(argc, argv, tmp);
	while (i < argc)
	{
		data->env = tmp;
		if (argv[i] != NULL)
		{
			name = ft_first_word(argv[i], '=', 0);
			if (get_env_var(tmp, name) == NULL)
			{
				new = new_env();
				if (new == NULL)
					return (free_multiple(1, &name), EXIT_FAILURE);
				new->name = name;
				new->value = ft_first_word(argv[i], '=', 1);
				new->next = NULL;
				while (tmp != NULL && tmp->next != NULL)
					tmp = tmp->next;
				tmp->next = new;
			}
			else
				free_multiple(1, &name);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
