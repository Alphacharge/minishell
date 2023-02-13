/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 18:57:22 by fkernbac          #+#    #+#             */
/*   Updated: 2023/02/13 14:12:27 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Creates an empty t_cmd node.*/
t_cmd	*create_cmd(t_data *data)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (cmd == NULL)
		return (set_error("malloc", NULL, 1, data), NULL);
	cmd->argv = NULL;
	cmd->data = data;
	cmd->name = NULL;
	cmd->param = NULL;
	cmd->next = NULL;
	cmd->prev = NULL;
	cmd->redir = NULL;
	cmd->here = false;
	cmd->type = EXEC;
	cmd->stdinsaver = FD_UNUSED;
	cmd->stdoutsaver = FD_UNUSED;
	cmd->fds[0] = FD_UNUSED;
	cmd->fds[1] = FD_UNUSED;
	cmd->reds[0] = FD_UNUSED;
	cmd->reds[1] = FD_UNUSED;
	return (cmd);
}
