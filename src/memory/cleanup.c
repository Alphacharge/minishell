/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 18:52:46 by fkernbac          #+#    #+#             */
/*   Updated: 2022/12/08 09:57:17 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

void	free_redirs(t_redir *current)
{
	t_redir	*prev;

	while (current != NULL)
	{
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
		free_ptr_array((void *)current->argv);
		free_params(current->param);
		free_redirs(current->redir);
		prev = current;
		current = current->next;
		ft_free(prev);
	}
	return (NULL);
}

void	ms_cleanup(t_data *data)
{
	close(data->hist.fd);
	rl_clear_history();
	delete_env(data->env);
	free(data->prompt->prompt);
	free(data->prompt->dir);
	free(data->prompt);
	free(data);
}
