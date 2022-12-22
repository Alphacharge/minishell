/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filedescriptors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 11:03:35 by rbetz             #+#    #+#             */
/*   Updated: 2022/12/22 11:15:22 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirects.h"
#include "execute.h"

void	close_and_neg(int *fd)
{
	if (VERBOSE == 1)
		printf("closing file descriptor %i\n", *fd);
	close(*fd);
	*fd = FD_UNUSED;
}

void	close_pipe_fds(t_cmd *cmd)
{
	if (cmd->fds[READ] != FD_UNUSED)
		close_and_neg(&cmd->fds[READ]);
	if (cmd->fds[WRITE] != FD_UNUSED)
		close_and_neg(&cmd->fds[WRITE]);
}

void	close_reds_fds(t_cmd *cmd)
{
	if (cmd->rats[READ] != FD_UNUSED)
		close_and_neg(&cmd->rats[READ]);
	if (cmd->rats[WRITE] != FD_UNUSED)
		close_and_neg(&cmd->rats[WRITE]);
}

void	close_piping(t_cmd *cmd)
{
	// first command, close only writeend of pipe
	if (cmd->prev == NULL && cmd->next != NULL)
		close_and_neg(&cmd->fds[WRITE]);
	// last command, close only readend of prev pipe
	else if (cmd->next == NULL && cmd->prev != NULL)
		close_and_neg(&cmd->prev->fds[READ]);
	// middle command, close readend of prev pipe and writeend of pipe
	else if (cmd->next != NULL && cmd->prev != NULL)
	{
		close_and_neg(&cmd->prev->fds[READ]);
		close_and_neg(&cmd->fds[WRITE]);
	}
}
