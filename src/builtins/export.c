/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 10:52:27 by rbetz             #+#    #+#             */
/*   Updated: 2023/02/08 10:18:53 by rbetz            ###   ########.fr       */
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

static void	add_new_env(t_env *env, char *name, char *value)
{
	t_env	*new;
	t_env	*tmp;

	tmp = env;
	new = new_env();
	if (new == NULL)
		free_multiple(2, name, value);
	new->name = name;
	new->value = value;
	new->next = NULL;
	while (tmp != NULL && tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}

static void	control_structure(char *argv, t_env *env)
{
	char	*name;
	char	*value;

	if (ft_posinset('=', argv) < 0)
		set_name_value(&name, &value, argv, 0);
	else
		set_name_value(&name, &value, argv, 1);
	if (get_env_var(env, name) == NULL)
		add_new_env(env, name, value);
	else
	{
		set_env_var(env, name, value);
		name = ft_free(name);
	}
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
			control_structure(argv[i], data->env);
		else
			return (ft_error("minishell: export", argv[i], 6));
		i++;
	}
	return (EXIT_SUCCESS);
}
