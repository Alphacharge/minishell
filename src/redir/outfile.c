/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 10:32:37 by rbetz             #+#    #+#             */
/*   Updated: 2023/01/31 18:38:24 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*if its a path just strdup it, if not*/
static void	check_outfiles(t_cmd *cmd, t_redir *redir)
{
	if (cmd->reds[WRITE] == FD_UNUSED && redir->type == OUTPUT)
		cmd->reds[WRITE] = open(redir->file, \
							O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (cmd->reds[WRITE] == FD_UNUSED && redir->type == APPEND)
		cmd->reds[WRITE] = open(redir->file, \
							O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
	{
		close_and_neg(&cmd->reds[WRITE]);
		check_outfiles(cmd, redir);
	}
printf("after checking outfiles: reds[0]: %i, reds[1]: %i\n", cmd->reds[0], cmd->reds[1]);
	if (cmd->reds[WRITE] < 0)
		ft_error(NULL, redir->file, 1);
}

/*goes through the cmd list and check 4 outfiles*/
t_cmd	*handle_outfiles(t_cmd *cmd)
{
	t_cmd	*tmp;
	t_redir	*tred;

printf("start of outfile: reds[0]: %i, reds[1]: %i\n", cmd->reds[0], cmd->reds[1]);
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
