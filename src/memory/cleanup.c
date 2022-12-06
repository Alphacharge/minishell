/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 18:52:46 by fkernbac          #+#    #+#             */
/*   Updated: 2022/12/06 12:39:33 by rbetz            ###   ########.fr       */
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
		free_ptr_array((void *)current->argv);
		// ft_free(current->name);
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
	// exit(0);
	delete_env(data->env);
	free(data->prompt->prompt);
	free(data->prompt->dir);
	free(data->prompt);
	// free_multiple(2, data->prompt.prompt, data->prompt);
	free(data);
}
