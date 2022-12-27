/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 10:32:37 by rbetz             #+#    #+#             */
/*   Updated: 2022/12/27 13:07:36 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirects.h"

/*if its a path just strdup it, if not*/
static void	check_outfiles(t_cmd *cmd, t_redir *redir)
{
	if (cmd->rats[WRITE] == FD_UNUSED && redir->type == OUTPUT)
		cmd->rats[WRITE] = open(redir->file, \
							O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (cmd->rats[WRITE] == FD_UNUSED && redir->type == APPEND)
		cmd->rats[WRITE] = open(redir->file, \
							O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
	{
		close_and_neg(&cmd->rats[WRITE]);
		check_outfiles(cmd, redir);
	}
	if (cmd->rats[WRITE] < 0)
		ft_error(NULL, redir->file, 1);
}

/*goes through the cmd list and check 4 outfiles*/
t_cmd	*handle_outfiles(t_cmd *cmd)
{
	t_cmd	*tmp;
	t_redir	*tred;

	tmp = cmd;
	while (tmp != NULL)
	{
		tred = tmp->redir;
		while (tred != NULL)
		{
			if (tred->type == OUTPUT || tred->type == APPEND)
				check_outfiles(tmp, tred);
			tred = tred->next;
		}
		tmp = tmp->next;
	}
	return (cmd);
}
