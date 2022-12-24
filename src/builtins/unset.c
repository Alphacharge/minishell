/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 10:52:36 by rbetz             #+#    #+#             */
/*   Updated: 2022/12/24 10:22:18 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

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

	tmp = data->env;
	prev = tmp;
	i = 1;
	if (argv[1] == NULL)
		return (ft_error(NULL, "unset", "not enough arguments"), EXIT_FAILURE);
	if (tmp == NULL)
		return (EXIT_FAILURE);
	while (argv[i] != NULL)
	{
		tmp = data->env;
		while (tmp != NULL && tmp->name != NULL && argv[i] != NULL)
			skip_or_unset(&prev, &tmp, argv[i], &data);
		i++;
	}
	return (EXIT_SUCCESS);
}
