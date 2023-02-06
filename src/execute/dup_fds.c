/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_fds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 17:51:01 by rbetz             #+#    #+#             */
/*   Updated: 2023/02/06 15:11:12 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	dup_middle_cmd(t_cmd *cmd)
{
	if (cmd->reds[WRITE] == FD_UNUSED)
	{
		if (dup2(cmd->fds[WRITE], STDOUT) < 0)
			ft_error(NULL, NULL, 9);
		close_and_neg(&cmd->fds[WRITE]);
	}
	if (cmd->reds[READ] == FD_UNUSED)
	{
		if (dup2(cmd->prev->fds[READ], STDIN) < 0)
			ft_error(NULL, NULL, 9);
		close_and_neg(&cmd->prev->fds[READ]);
	}
}

void	dup_pipe_fds(t_cmd *cmd)
{
	if (cmd->reds[WRITE] == FD_UNUSED && cmd->prev == NULL && cmd->next != NULL)
	{
		if (dup2(cmd->fds[WRITE], STDOUT) < 0)
			ft_error(NULL, NULL, 9);
		close_and_neg(&cmd->fds[WRITE]);
	}
	else if (cmd->reds[READ] == FD_UNUSED
		&& cmd->next == NULL && cmd->prev != NULL)
	{
		if (dup2(cmd->prev->fds[READ], STDIN) < 0)
			ft_error(NULL, NULL, 9);
		close_and_neg(&cmd->prev->fds[READ]);
	}
	else if (cmd->next != NULL && cmd->prev != NULL)
		dup_middle_cmd(cmd);
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
