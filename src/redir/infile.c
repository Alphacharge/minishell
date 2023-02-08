/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 10:13:54 by rbetz             #+#    #+#             */
/*   Updated: 2023/02/08 09:50:13 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*check if the input is the last one*/
static int	last_input(t_redir *redir)
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
void	check_infiles(t_cmd *cmd, t_redir *redir)
{
	int	success;

	success = 1;
	if (access(redir->file, F_OK) != 0)
	{
		success = 0;
		ft_error(NULL, redir->file, 1);
	}
	if (success == 1 && access(redir->file, R_OK) != 0)
	{
		success = 0;
		ft_error(NULL, redir->file, 1);
	}
	if (success == 0)
	{
		cmd->error = true;
		cmd->reds[READ] = dup(STDIN);
	}
}

/*close fd from heredoc if exist and read from infile*/
static void	read_infile(t_cmd *cmd, t_redir *redir)
{
	if (cmd->reds[READ] == FD_UNUSED)
	{
		cmd->reds[READ] = open(redir->file, O_RDONLY);
		if (cmd->reds[READ] == -1)
		{
			ft_error(NULL, redir->file, 1);
			cmd->error = true;
		}
	}
	else
	{
		close_and_neg(&cmd->reds[READ]);
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
				if (tmp->error == false && last_input(tred) == 1)
					read_infile(tmp, tred);
			}
			tred = tred->next;
		}
		tmp = tmp->next;
	}
	return (cmd);
}
