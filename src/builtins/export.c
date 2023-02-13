/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 10:52:27 by rbetz             #+#    #+#             */
/*   Updated: 2023/02/13 17:57:16 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_name_value(char **name, char **value, char *argv, int flag)
{
	if (flag == 0)
	{
		(*name) = ft_strdup(argv);
		(*value) = ft_strdup("");
	}
	else
	{
		(*name) = ft_first_word(argv, '=', 0);
		(*value) = ft_first_word(argv, '=', 1);
	}
}

static t_env	*add_new_env(t_env *env, char *name, char *value)
{
	t_env	*new;

	new = new_env();
	if (new == NULL)
		free_multiple(2, name, value);
	new->name = name;
	new->value = value;
	if (env != NULL)
		new->next = env;
	else
		new->next = NULL;
	env = new;
	return (env);
}

static t_env	*control_structure(char *argv, t_env *env)
{
	char	*name;
	char	*value;

	if (ft_posinset('=', argv) < 0)
		set_name_value(&name, &value, argv, 0);
	else
		set_name_value(&name, &value, argv, 1);
	if (get_env_var(env, name) == NULL)
		env = add_new_env(env, name, value);
	else
	{
		set_env_var(env, name, value);
		name = ft_free(name);
	}
	return (env);
}

int	export(int argc, char **argv, t_data *data)
{
	int		i;

	i = 1;
	if (argc == 1)
		export_print(data->env);
	while (i < argc)
	{
		if (is_valid_var(argv[i]))
			data->env = control_structure(argv[i], data->env);
		else
			return (ft_error("minishell: export", argv[i], 6));
		i++;
	}
	return (EXIT_SUCCESS);
}
