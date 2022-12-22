/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_fds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 17:51:01 by rbetz             #+#    #+#             */
/*   Updated: 2022/12/22 17:53:53 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void dup_pipe_fds(t_cmd *cmd)
{
	if (cmd->rats[WRITE] == FD_UNUSED && cmd->prev == NULL && cmd->next != NULL)
	{
		// ft_putendl_fd("-->1", 2);
		if (dup2(cmd->fds[WRITE], STDOUT) < 0)
			ft_error(NULL, NULL, "Error dup first cmd");
		close_and_neg(&cmd->fds[WRITE]);
	}
	else if (cmd->rats[READ] == FD_UNUSED && cmd->next == NULL && cmd->prev != NULL)
	{
		// ft_putendl_fd("-->2", 2);
		if (dup2(cmd->prev->fds[READ], STDIN) < 0)
			ft_error(NULL, NULL, "Error dup last cmd");
		close_and_neg(&cmd->prev->fds[READ]);
	}
	else if (cmd->rats[WRITE] == FD_UNUSED && cmd->rats[READ] == FD_UNUSED && cmd->next != NULL && cmd->prev != NULL)
	{
		// ft_putendl_fd("-->3", 2);
		if (dup2(cmd->fds[WRITE], STDOUT) < 0 || dup2(cmd->prev->fds[READ], STDIN) < 0)
			ft_error(NULL, NULL, "Error dup mid cmd");
		close_and_neg(&cmd->prev->fds[READ]);
		close_and_neg(&cmd->fds[WRITE]);
	}
}

void	dup_reds_fds(t_cmd *cmd)
{
	if (cmd->rats[READ] != FD_UNUSED)
	{
		// ft_putendl_fd("-->4", 2);
		if (dup2(cmd->rats[READ], STDIN) < 0)
			ft_error(NULL, NULL, "Error dup file in cmd");
		close_and_neg(&cmd->rats[READ]);
	}
	if (cmd->rats[WRITE] != FD_UNUSED)
	{
		// ft_putendl_fd("-->5", 2);
		if (dup2(cmd->rats[WRITE], STDOUT) < 0)
			ft_error(NULL, NULL, "Error dup file out cmd");
		close_and_neg(&cmd->rats[WRITE]);
	}
}
