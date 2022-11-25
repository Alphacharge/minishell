/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 19:00:43 by fkernbac          #+#    #+#             */
/*   Updated: 2022/11/25 17:06:05 by rbetz            ###   ########.fr       */
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

void	*free_cmds(t_cmd *current);
void	ms_cleanup(t_data *data);

#endif
