/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humbi <humbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 10:13:54 by rbetz             #+#    #+#             */
/*   Updated: 2022/12/15 11:34:40 by humbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirects.h"

/*check for an other fd, these one should be from a infile, and close it*/
/*then call itsself and create a new one*/
static void check_infiles(t_cmd *cmd, t_redir *redir)
{
	int success;

	success = 1;
	if (access(redir->file, F_OK) != 0)
	{
		success = 0;
		ft_error("No such file or directory");
	}
	if (success == 1 && access(redir->file, R_OK) != 0)
	{
		success = 0;
		ft_error("Permission denied");
	}
	if (success == 0)
	{
		cmd->error = true;
		cmd->rats[READ] = dup(STDIN);
	}
	if (cmd->here == false && success == 1)
	{
		if (cmd->rats[READ] == FD_UNUSED)
		{
			cmd->rats[READ] = open(redir->file, O_RDONLY);
			if (cmd->rats[READ] == -1)
			{
				ft_error("Error opening file");
				cmd->error = true;
			}
		}
		else
		{
			close_and_neg(&cmd->rats[READ]);
			check_infiles(cmd, redir);
		}
	}
}

/*goes through the cmd list and check 4 infiles*/
/*if there is already a fd we have a heredoc and leave instantly*/
t_cmd *handle_infiles(t_cmd *cmd)
{
	t_cmd *tmp;
	t_redir *tred;

	tmp = cmd;
	while (tmp != NULL)
	{
		tred = tmp->redir;
		while (tred != NULL)
		{
			if (tred->r_type == INPUT)
				check_infiles(tmp, tred);
			tred = tred->next;
		}
		tmp = tmp->next;
	}
	return (cmd);
}
