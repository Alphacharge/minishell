/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filedescriptors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 11:03:35 by rbetz             #+#    #+#             */
/*   Updated: 2023/01/31 20:40:32 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_and_neg(int *fd)
{
	if (VERBOSE == 1)
		printf("closing file descriptor %i\n", *fd);
	close(*fd);
	*fd = FD_UNUSED;
}

void	close_pipe_fds(t_cmd *cmd)
{
	if (cmd->pipe[READ] != FD_UNUSED)
		close_and_neg(&cmd->pipe[READ]);
	if (cmd->pipe[WRITE] != FD_UNUSED)
		close_and_neg(&cmd->pipe[WRITE]);
}

void	close_reds_fds(t_cmd *cmd)
{
	if (cmd->reds[READ] != FD_UNUSED)
		close_and_neg(&cmd->reds[READ]);
	if (cmd->reds[WRITE] != FD_UNUSED)
		close_and_neg(&cmd->reds[WRITE]);
}

void	close_piping(t_cmd *cmd)
{
	if (cmd->prev == NULL && cmd->next != NULL)
		close_and_neg(&cmd->pipe[WRITE]);
	else if (cmd->next == NULL && cmd->prev != NULL)
		close_and_neg(&cmd->prev->pipe[READ]);
	else if (cmd->next != NULL && cmd->prev != NULL)
	{
		close_and_neg(&cmd->prev->pipe[READ]);
		close_and_neg(&cmd->pipe[WRITE]);
	}
}
