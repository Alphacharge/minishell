/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 18:52:46 by fkernbac          #+#    #+#             */
/*   Updated: 2022/11/29 13:52:01 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

void	free_redirs (t_redir *current)
{
	t_redir	*prev;

	while (current != NULL)
	{
		// free(current->file);
		prev = current;
		current = current->next;
		free (prev);
	}
}

void	free_params(t_param *current)
{
	t_param	*prev;

	while (current != NULL)
	{
		// free(current->arg);
		prev = current;
		current = current->next;
		free (prev);
	}
}

void	*free_cmds(t_cmd *current)
{
	t_cmd	*prev;

	while (current != NULL)
	{
		// free_ptr_array((void *)current->argv);
		// ft_free(current->name);
		free_params(current->param);
		free_redirs(current->redir);
		prev = current;
		current = current->pipe;
		ft_free(prev);
	}
	return (NULL);
}
