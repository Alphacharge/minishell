/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 09:32:07 by rbetz             #+#    #+#             */
/*   Updated: 2022/10/28 13:20:07 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errorhandling.h"

static void	subclean(t_var *var)
{
	int	i;

	i = 0;
	if (var->fd_in >= 0)
		close(var->fd_in);
	if (var->fd_out >= 0)
		close(var->fd_out);
	if (var->pwd != NULL)
		free(var->pwd);
	if (var->exec != NULL)
		free(var->exec);
	if (var->path != NULL)
	{
		while (var->path[i] != NULL)
			free(var->path[i++]);
		free(var->path);
	}
}

static void	subclean_array(t_var *var)
{
	int	i;
	int	j;

	if (var->args != NULL)
	{
		i = 0;
		while (var->args[i] != NULL)
		{
			j = 0;
			while (var->args[i][j] != NULL)
				free(var->args[i][j++]);
			free(var->args[i++]);
		}
		free(var->args);
	}
}

void	clean(t_var *var)
{
	subclean(var);
	subclean_array(var);
	if (var != NULL)
		free(var);
}