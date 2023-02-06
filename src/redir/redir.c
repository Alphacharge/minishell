/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 10:32:37 by rbetz             #+#    #+#             */
/*   Updated: 2023/02/06 15:12:23 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*create_redirs(t_cmd *cmd, t_data *data)
{
	t_cmd	*tmp;
	t_redir	*tred;

	cmd = handle_heredocs(cmd, data);
	tmp = cmd;
	while (tmp != NULL)
	{
		tred = tmp->redir;
		while (tred != NULL)
		{
			if (tred->type == INPUT)
				check_infiles(tmp, tred);
			if (tred->type == OUTPUT || tred->type == APPEND)
				check_outfiles(tmp, tred);
			if (tmp->error == true)
				break ;
			tred = tred->next;
		}
		tmp = tmp->next;
	}
	cmd = handle_infiles(cmd);
	return (cmd);
}
