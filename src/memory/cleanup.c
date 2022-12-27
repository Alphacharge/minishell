/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 18:52:46 by fkernbac          #+#    #+#             */
/*   Updated: 2022/12/27 16:46:43 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"
#include "execute.h"

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

/*Frees every node of the linked list, but assumes nothing is allocated
within.*/
void	*free_cmds_error(t_cmd *cmd)
{
	t_cmd	*prev;

	while (cmd != NULL)
	{
		free_params(cmd->param);
		free_redirs(cmd->redir);
		prev = cmd;
		cmd = cmd->next;
		ft_free(prev);
	}
	return (NULL);
}

/*Frees every node of the linked list, including allocated strings.*/
void	*free_cmds(t_cmd *current)
{
	t_cmd	*prev;

	while (current != NULL)
	{
		free_ptr_array((void *)current->argv);
		free_params(current->param);
		free_redirs(current->redir);
		close_pipe_fds(current);
		close_reds_fds(current);
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
	ft_free(data->exitstatus);
	free(data);
}
