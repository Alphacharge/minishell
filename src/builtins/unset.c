/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 10:52:36 by rbetz             #+#    #+#             */
/*   Updated: 2023/02/03 17:18:58 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	varname_error(char *var)
{
	if (*skip_var(var) != '\0')
	{
		ft_error("minishell: unset", var, 6);
		return (0);
	}
	return (1);
}

static void	skip_or_unset(t_env **prev, t_env **tmp, char *argv, t_data **data)
{
	if (ft_strcmp(argv, (*tmp)->name) != 0)
	{
		(*prev) = (*tmp);
		(*tmp) = (*tmp)->next;
	}
	else
	{
		if ((*tmp) == (*data)->env)
		{
			(*data)->env = (*tmp)->next;
			(*prev) = (*data)->env;
		}
		else
			(*prev)->next = (*tmp)->next;
		(*tmp)->next = NULL;
		delete_env((*tmp));
		(*tmp) = NULL;
	}
}

/*deletes all given vars from env if they exist,*/
/*returns NULL if env is empty or env*/
int	unset(char **argv, t_data *data)
{
	t_env	*tmp;
	t_env	*prev;
	int		i;
	int		error;

	tmp = data->env;
	prev = tmp;
	i = 1;
	error = 0;
	if (argv[1] == NULL)
		return (EXIT_SUCCESS);
	if (tmp == NULL)
		return (EXIT_FAILURE);
	while (argv[i] != NULL)
	{
		tmp = data->env;
		if (varname_error(argv[i]) == 0)
			error = 1;
		else
			while (argv[i] != NULL && tmp != NULL && tmp->name != NULL)
				skip_or_unset(&prev, &tmp, argv[i], &data);
		i++;
	}
	return (error);
}
