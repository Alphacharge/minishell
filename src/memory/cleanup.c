/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 18:52:46 by fkernbac          #+#    #+#             */
/*   Updated: 2022/11/08 19:00:19 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

void	*free_cmds(t_cmd *current)
{
	t_cmd	*prev;

	prev = NULL;
	if (current == NULL)
		return (NULL);
	while (current->next != NULL)
	{
		prev = current;
		current = current->next;
		ft_free(prev);
	}
	return (ft_free(current));
}
