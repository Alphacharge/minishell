/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_progs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 16:00:51 by rbetz             #+#    #+#             */
/*   Updated: 2022/10/28 13:17:10 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "parsing.h"

static void	sample(t_var *var, int i, int j)
{
	if (var->exec != NULL)
		free(var->exec);
	if (ft_strchr(var->args[j][0], '/') == 0)
		var->exec = combine_pathprog(var->path[i], var->args[j][0]);
	else
		var->exec = ft_strdup(var->args[j][0]);
}

static void	split_arg(t_var *var, char **argv, int i)
{
	while (i++ <= var->calls + var->here)
	{
		var->args[i - 2 - var->here] = ft_split(argv[i], ' ');
		if (var->args[i - 2 - var->here] == NULL
			|| ft_strlen(var->args[i - 2 - var->here][0]) == 0)
			ft_error(var, 8);
	}
}

void	parse_progs(t_var *var, char **argv, char **envp)
{
	int		i;
	int		j;

	i = 1 + var->here;
	split_arg(var, argv, i);
	j = 0;
	while (j <= (var->calls - var->here -1))
	{
		i = 0;
		var->scs = -1;
		while (var->path[i] != NULL && var->scs != 0)
		{
			sample(var, i, j);
			var->scs = access(var->exec, F_OK);
			i++;
		}
		if (var->scs != 0)
		{
			close_fds(var);
			ft_error(var, 8);
		}
		execute_programs(var, envp);
		j++;
	}
}
