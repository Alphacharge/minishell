/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 10:32:37 by rbetz             #+#    #+#             */
/*   Updated: 2022/12/22 19:27:50 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirects.h"
#include "execute.h"

t_cmd	*create_redirs(t_cmd *cmd, t_data *data)
{
	cmd = handle_heredocs(cmd, data);
	cmd = handle_infiles(cmd);
	cmd = handle_outfiles(cmd);
	return (cmd);
}
