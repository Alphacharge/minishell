/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 18:52:46 by fkernbac          #+#    #+#             */
/*   Updated: 2023/02/13 15:59:30 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_redirs(t_redir *current)
{
	t_redir	*prev;

	while (current != NULL)
	{
		prev = current;
		if (current->file != NULL)
			current->file = ft_free(current->file);
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
	t_redir	*prev_redir;
	t_redir	*current_redir;

	while (cmd != NULL)
	{
		free_params(cmd->param);
		current_redir = cmd->redir;
		while (current_redir != NULL)
		{
			prev_redir = current_redir;
			current_redir = current_redir->next;
			ft_free(prev_redir);
		}
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
	free(data);
}
