/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 18:52:46 by fkernbac          #+#    #+#             */
/*   Updated: 2022/11/15 14:45:22 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"
#include "utils.h"

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
