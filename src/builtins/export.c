/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humbi <humbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 10:52:27 by rbetz             #+#    #+#             */
/*   Updated: 2023/01/28 14:52:40 by humbi            ###   ########.fr       */
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

static t_env	*add_new_env(char **name, char **value, t_env **tmp)
{
	t_env	*new;

	new = new_env();
	if (new == NULL)
		return (free_multiple(1, (*name)), NULL);
	new->name = (*name);
	new->value = (*value);
	new->next = NULL;
	while ((*tmp) != NULL && (*tmp)->next != NULL)
		(*tmp) = (*tmp)->next;
	return (new);
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
			if (ft_posinset('=', argv[i]) < 0)
				set_name_value(&name, &value, argv[i], 0);
			else
				set_name_value(&name, &value, argv[i], 1);
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

static void	control_structur(char **name, char **value, char *argv, t_env **tmp)
{
	if (ft_posinset('=', argv) < 0)
		set_name_value(name, value, argv, 0);
	else
		set_name_value(name, value, argv, 1);
	if (get_env_var((*tmp), (*name)) == NULL)
		(*tmp)->next = add_new_env(name, value, tmp);
	else
		free_multiple(1, name);
}

int	export(int argc, char **argv, t_data *data)
{
	t_env	*tmp;
	char	*name;
	char	*value;
	int		i;

	tmp = data->env;
	i = 1;
	if (argc == 1)
		export_print(tmp);
	tmp = update_values(argc, argv, tmp);
	while (i < argc)
	{
		data->env = tmp;
		if (argv[i] != NULL && is_valid_var(argv[i]))
			control_structur(&name, &value, argv[i], &tmp);
		else
			return (ft_error("minishell: export", argv[i], 6));
		i++;
	}
	return (EXIT_SUCCESS);
}
