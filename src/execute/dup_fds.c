/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_fds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 17:51:01 by rbetz             #+#    #+#             */
/*   Updated: 2023/01/31 20:47:25 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup_pipe_fds(t_cmd *cmd)
{
	if (cmd->reds[WRITE] == FD_UNUSED && cmd->prev == NULL && cmd->next != NULL)
	{
		if (dup2(cmd->pipe[WRITE], STDOUT) < 0)
			ft_error(NULL, NULL, 9);
		close_and_neg(&cmd->pipe[WRITE]);
	}
	else if (cmd->reds[READ] == FD_UNUSED
		&& cmd->next == NULL && cmd->prev != NULL)
	{
		if (dup2(cmd->prev->pipe[READ], STDIN) < 0)
			ft_error(NULL, NULL, 9);
		close_and_neg(&cmd->prev->pipe[READ]);
	}
	else if (cmd->reds[WRITE] == FD_UNUSED && cmd->reds[READ] == FD_UNUSED
		&& cmd->next != NULL && cmd->prev != NULL)
	{
		if (dup2(cmd->pipe[WRITE], STDOUT) < 0
			|| dup2(cmd->prev->pipe[READ], STDIN) < 0)
			ft_error(NULL, NULL, 9);
		close_and_neg(&cmd->prev->pipe[READ]);
		close_and_neg(&cmd->pipe[WRITE]);
	}
}

void	dup_reds_fds(t_cmd *cmd)
{
	if (cmd->reds[READ] != FD_UNUSED)
	{
		if (dup2(cmd->reds[READ], STDIN) < 0)
			ft_error(NULL, NULL, 9);
		close_and_neg(&cmd->reds[READ]);
	}
	if (cmd->reds[WRITE] != FD_UNUSED)
	{
		if (dup2(cmd->reds[WRITE], STDOUT) < 0)
			ft_error(NULL, NULL, 9);
		close_and_neg(&cmd->reds[WRITE]);
	}
}
