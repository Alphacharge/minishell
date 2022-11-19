/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 18:52:46 by fkernbac          #+#    #+#             */
/*   Updated: 2022/11/19 12:00:18 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

void	*free_cmds(t_cmd *current)
{
	t_cmd	*prev;

	while (current != NULL)
	{
		free_ptr_array((void *)current->argv);
		prev = current;
		current = current->next;
		ft_free(prev);
	}
	return (NULL);
}
