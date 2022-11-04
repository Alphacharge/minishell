/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 09:34:57 by rbetz             #+#    #+#             */
/*   Updated: 2022/11/04 14:54:27 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filedescriptors.h"

void	close_fds(t_var *var)
{
	if (var->index_fd == 0)
		close(var->fds[var->index_fd][1]);
	else if (var->index_fd == var->calls - 1)
		close(var->fds[var->index_fd - 1][0]);
	else
	{
		close(var->fds[var->index_fd - 1][0]);
		close(var->fds[var->index_fd][1]);
	}
	if (var->here)
		close(var->here_fd[0]);
}

void	first_fd(t_var *var)
{
	if (var->here)
	{
		if (dup2(var->here_fd[0], 0) < 0
			|| dup2(var->fds[var->index_fd][1], 1) < 0)
			ft_error(var, 9);
		close(var->here_fd[0]);
	}
	else
	{
		if (dup2(var->fd_in, 0) < 0
			|| dup2(var->fds[var->index_fd][1], 1) < 0)
			ft_error(var, 9);
		close(var->fd_in);
	}
}
