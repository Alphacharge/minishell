/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humbi <humbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 10:32:37 by rbetz             #+#    #+#             */
/*   Updated: 2022/12/17 14:32:23 by humbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirects.h"


/*if its a path just strdup it, if not*/
static void check_outfiles(t_cmd *cmd, t_redir *redir)
{
	if (cmd->rats[WRITE] != FD_UNUSED && redir->r_type == OUTPUT)
		cmd->rats[WRITE] = open(redir->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (cmd->rats[WRITE] != FD_UNUSED && redir->r_type == APPEND)
		cmd->rats[WRITE] = open(redir->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
	{
		close_and_neg(&cmd->rats[WRITE]);
		check_outfiles(cmd, redir);
	}
	if (cmd->rats[WRITE] < 0)
		ft_error("Error opening file");
}

/*goes through the cmd list and check 4 outfiles*/
t_cmd *handle_outfiles(t_cmd *cmd)
{
	t_cmd *tmp;
	t_redir *tred;

	tmp = cmd;
	while (tmp != NULL)
	{
		tred = tmp->redir;
		while (tred != NULL)
		{
			if (tred->r_type == OUTPUT || tred->r_type == APPEND)
				check_outfiles(tmp, tred);
			tred = tred->next;
		}
		tmp = tmp->next;
	}
	return (cmd);
}