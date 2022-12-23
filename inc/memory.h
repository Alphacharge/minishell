/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 19:00:43 by fkernbac          #+#    #+#             */
/*   Updated: 2022/12/22 18:32:21 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMORY_H
# define MEMORY_H

# include "structs.h"
# include "utils.h"
# include "environment.h"
# include "history.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdlib.h>

void	*free_cmds(t_cmd *cmd);
void	*free_cmds_error(t_cmd *cmd);
void	close_fds(t_cmd	*cmd);
void	ms_cleanup(t_data *data);

#endif
