/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 10:13:54 by rbetz             #+#    #+#             */
/*   Updated: 2022/12/09 11:57:11 by rbetz            ###   ########.fr       */
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
		cmd->error = true;
	if (cmd->here == false && success == 1)
	{
		if (cmd->rats[0] == INT32_MIN)
		{
			cmd->rats[0] = open(redir->file, O_RDONLY);
			if (cmd->rats[0] == -1)
			{
				ft_error("Error opening file");
				cmd->error = true;
			}
		}
		else
		{
			close_and_neg(&cmd->rats[0]);
			check_infiles(cmd, redir);
		}
	}
	// ft_putendl_fd("end checkinfile", 2);
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
			// if (tmp->rats[0] != INT32_MIN)
			// 	break ;
			if (tred->r_type == INPUT)
				check_infiles(tmp, tred);
			tred = tred->next;
		}
		tmp = tmp->next;
	}
	return (cmd);
}
