/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 16:49:45 by fkernbac          #+#    #+#             */
/*   Updated: 2023/02/13 19:42:46 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Adds string as next parameter or as command name if no command is set yet.*/
static char	*add_arg(t_cmd *cmd, char *s)
{
	t_param	*current;
	t_param	*param;

	current = cmd->param;
	if (*s == '\0' || cmd == NULL)
		return (s);
	if (cmd->name == NULL)
	{
		cmd->name = s;
		return (skip_argument(s));
	}
	param = ft_calloc(1, sizeof(t_param));
	param->arg = s;
	param->next = NULL;
	if (cmd->param == NULL)
		cmd->param = param;
	else
	{
		while (current != NULL && current->next != NULL)
			current = current->next;
		current->next = param;
	}
	s = skip_argument(s);
	return (s);
}

/*Iterates over string and splits it into fitting structs.*/
static int	split_input(char *s, t_cmd *cmd, t_data *data)
{
	while (*s != '\0')
	{
		s = null_whitespace(s);
		if (*s == '\0')
			break ;
		if (*s == '>' || *s == '<')
		{
			s = new_redir(cmd, s);
			if (s == NULL)
				return (1);
		}
		else if (*s == '|')
		{
			if (cmd->name == NULL)
				return (1);
			cmd->next = create_cmd(data);
			cmd->next->prev = cmd;
			cmd = cmd->next;
			s = null_increment(s);
		}
		else
			s = add_arg(cmd, s);
	}
	return (0);
}

/*Checks entire linked list for possible input errors.*/
static int	check_syntax(t_cmd *lst)
{
	t_redir	*current_redir;

	while (lst != NULL)
	{
		if (lst->name == NULL || lst->name[0] == 0)
			return (1);
		current_redir = lst->redir;
		while (current_redir != NULL)
		{
			if (current_redir->file == NULL || current_redir->file[0] == 0)
				return (1);
			current_redir = current_redir->next;
		}
		lst = lst->next;
	}
	return (0);
}

/*Converts the input string s to a linked list and returns head node.*/
t_cmd	*input_to_lst(char *s, t_data *data)
{
	if (s == NULL || *s == '\0')
		return (NULL);
	data->cmd_head = create_cmd(data);
	if (split_input(s, data->cmd_head, data) != 0 \
		||check_syntax(data->cmd_head) != 0)
	{
		data->exitstatus = ft_error(NULL, NULL, 10);
		free_cmds_error(data->cmd_head);
		return (NULL);
	}
	return (data->cmd_head);
}
