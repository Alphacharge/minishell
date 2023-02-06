/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 10:32:37 by rbetz             #+#    #+#             */
/*   Updated: 2023/02/06 15:12:00 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*if its a path just strdup it, if not*/
void	check_outfiles(t_cmd *cmd, t_redir *redir)
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
	if (cmd->reds[WRITE] < 0)
		ft_error(NULL, redir->file, 1);
}
