/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 18:57:22 by fkernbac          #+#    #+#             */
/*   Updated: 2023/02/07 18:58:09 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Creates an empty t_cmd node.*/
t_cmd	*create_cmd(t_data *data)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (cmd == NULL)
		return (ft_error("malloc", NULL, 1), NULL);
	cmd->argv = NULL;
	cmd->data = data;
	cmd->name = NULL;
	cmd->param = NULL;
	cmd->next = NULL;
	cmd->prev = NULL;
	cmd->redir = NULL;
	cmd->here = false;
	cmd->type = EXEC;
	cmd->fds[0] = FD_UNUSED;
	cmd->fds[1] = FD_UNUSED;
	cmd->reds[0] = FD_UNUSED;
	cmd->reds[1] = FD_UNUSED;
	return (cmd);
}