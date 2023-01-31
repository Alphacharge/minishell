/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 10:32:37 by rbetz             #+#    #+#             */
/*   Updated: 2023/01/31 20:29:16 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	create_outfile(t_cmd *cmd, t_redir *redir)
{
	if (cmd->reds[WRITE] != FD_UNUSED)
		close_and_neg(&cmd->reds[WRITE]);
	if (redir->type == OUTPUT)
		cmd->reds[WRITE] = open(redir->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (redir->type == APPEND)
		cmd->reds[WRITE] = open(redir->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (cmd->reds < 0)
		return (ft_error(NULL, redir->file, 1));
	return (0);
}

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
static int	check_infile(t_cmd *cmd, t_redir *redir)
{
	if (access(redir->file, F_OK) != 0 || access(redir->file, R_OK) != 0)
	{
		close(cmd->reds[READ]);
		close(cmd->reds[WRITE]);
		cmd->error = true;
		return (ft_error(NULL, redir->file, 1));
	}
	// if (success == 0)
	// 	cmd->reds[READ] = dup(STDIN);
	return (0);
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

t_cmd	*create_redirs(t_cmd *cmd, t_data *data)
{
	//bash stops execution as soon as a broken infile or outfile is read
	cmd = handle_heredocs(cmd, data);
	// cmd = handle_infiles(cmd);
	// cmd = handle_outfiles(cmd);

	t_cmd	*current;
	t_redir	*current_redir;

	current = cmd;
	while (current != NULL)
	{
		current_redir = current->redir;
		while (current_redir != NULL)
		{
			if (current_redir->type == INPUT)
			{
				if (check_infile(current, current_redir) != 0)
					break ;
				if (current->error == false && last_input(current_redir) == 1)
					read_infile(current, current_redir);
			}
			else if (current_redir->type != HERE)
				if (create_outfile(current, current_redir) != 0)
					break ;
			current_redir = current_redir->next;
		}
		current = current->next;
	}
	return (cmd);
}
