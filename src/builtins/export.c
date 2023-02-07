/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 10:52:27 by rbetz             #+#    #+#             */
/*   Updated: 2023/02/07 18:01:54 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*add_new_env(char *name, char *value, t_env *env)
{
	t_env	*new;

	new = new_env();
	if (new == NULL)
		return (ft_free(name), ft_free(value));
	new->name = name;
	new->value = value;
	new->next = NULL;
	while (env != NULL && env->next != NULL)
		env = env->next;
	env->next = new;
	return (new);
}

static int	var_exists(char *s, t_env *env)
{
	t_env	*current;

	current = env;
	while (current != NULL && ft_strcmp(s, current->name) != 0)
		current = current->next;
	if (current == NULL)
		return (0);
	return (1);
}

static char	*parameter_error(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (is_valid_var(argv[i]) == 0)
			return (argv[i]);
		i++;
	}
	return (NULL);
}

int	export(int argc, char **argv, t_data *data)
{
	char	*name;
	int		i;

	i = 1;
	if (argc == 1)
		export_print(data->env);
	if (parameter_error(argc, argv) != NULL)
		return (ft_error("minishell: export", parameter_error(argc, argv), 6));
	while (i < argc)
	{
		name = ft_first_word(argv[i], '=', 0);
		if (var_exists(name, data->env) == 1 && ft_posinset('=', argv[i]) > 0)
		{
			set_env_var(data->env, name, ft_first_word(argv[i], '=', 1));
			name = ft_free(name);
		}
		else if (ft_posinset('=', argv[i]) > 0)
			add_new_env(name, ft_first_word(argv[i], '=', 1), data->env);
		else
			add_new_env(name, ft_strdup(""), data->env);
		i++;
	}
	return (EXIT_SUCCESS);
}
