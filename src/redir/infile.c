/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humbi <humbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 10:13:54 by rbetz             #+#    #+#             */
/*   Updated: 2023/01/28 14:14:54 by humbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirects.h"

/*check if the input is the last one*/
static int last_input(t_redir *redir)
{
	if (redir == NULL)
		return (0);
	redir = redir->next;
	while (redir != NULL)
	{
		if (redir->type == INPUT || redir->type == HERE)
			return (0);
		redir = redir->next;
	}
	return (1);
}

/*check for an other fd, these one should be from a infile, and close it*/
/*then call itsself and create a new one*/
static void	check_infiles(t_cmd *cmd, t_redir *redir)
{
	int	success;

	success = 1;
	if (access(redir->file, F_OK) != 0)
	{
		success = 0;
		ft_error(NULL, NULL, "No such file or directory");
	}
	if (success == 1 && access(redir->file, R_OK) != 0)
	{
		success = 0;
		ft_error(NULL, NULL, "Permission denied");
	}
	if (success == 0)
	{
		cmd->error = true;
		cmd->rats[READ] = dup(STDIN);
	}
}

/*close fd from heredoc if exist and read from infile*/
static void	read_infile(t_cmd *cmd, t_redir *redir)
{
	if (cmd->rats[READ] == FD_UNUSED)
	{
		cmd->rats[READ] = open(redir->file, O_RDONLY);
		if (cmd->rats[READ] == -1)
		{
			ft_error(NULL, NULL, "Error opening file");
			cmd->error = true;
		}
	}
	else
	{
		close_and_neg(&cmd->rats[READ]);
		read_infile(cmd, redir);
	}
}

/*goes through the cmd list and check 4 infiles*/
/*if there is already a fd from here we check if it is the last input*/
t_cmd	*handle_infiles(t_cmd *cmd)
{
	t_cmd	*tmp;
	t_redir	*tred;

	tmp = cmd;
	while (tmp != NULL)
	{
		tred = tmp->redir;
		while (tred != NULL)
		{
			if (tred->type == INPUT)
			{
				check_infiles(tmp, tred);
				if (tmp->error == false && last_input(tred) == 1)
					read_infile(tmp, tred);
			}
			tred = tred->next;
		}
		tmp = tmp->next;
	}
	return (cmd);
}
