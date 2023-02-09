/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 16:49:45 by fkernbac          #+#    #+#             */
/*   Updated: 2023/02/09 19:26:04 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Appends a new t_redir node at the last t_redir node of cmd.*/
static void	append_redir(t_cmd *cmd, t_redir *r)
{
	t_redir	*current;

	current = cmd->redir;
	if (current == NULL)
	{
		cmd->redir = r;
		return ;
	}
	while (current != NULL && current->next != NULL)
		current = current->next;
	current->next = r;
}

/*Adds the first redirection found in s as new t_redir node to cmd.*/
static char	*new_redir(t_cmd *cmd, char *s)
{
	t_redir	*r;

	r = ft_calloc(1, sizeof(t_redir));
	if (r == NULL)
		return (cmd->data->exitstatus = ft_error("malloc", NULL, 1), NULL);
	r->file = NULL;
	r->next = NULL;
	if (*s == '<' && *(s + 1) == '<')
		r->type = HERE;
	else if (*s == '>' && *(s + 1) == '>')
		r->type = APPEND;
	else if (*s == '<')
		r->type = INPUT;
	else
		r->type = OUTPUT;
	if ((*s == '<' && *(s + 1) == '<') || (*s == '>' && *(s + 1) == '>'))
		s = null_increment(s);
	s = null_increment(s);
	s = null_whitespace(s);
	if (is_token(*s) == true || *s == 0)
		return (ft_free(r));
	r->file = s;
	append_redir(cmd, r);
	return (skip_argument(s));
}

/*Adds string as next parameter or as command name if no command is set yet.*/
static char	*add_arg(t_cmd *cmd, char *s)
{
	t_param	*current;
	t_param	*param;

	current = cmd->param;
	if (*s == '\0' || cmd == NULL)
		return (s);
	if (cmd->name == NULL)
		return (cmd->name = s, skip_argument(s));
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
	while (*s != 0)
	{
		s = null_whitespace(s);
		if (*s == 0)
			break ;
		if (*s == '>' || *s == '<')
		{
			s = new_redir(cmd, s);
			if (s == NULL)
				return (EXIT_FAILURE);
		}
		else if (*s == '|')
		{
			if (cmd->name == NULL)
				return (EXIT_FAILURE);
			cmd->next = create_cmd(data);
			cmd->next->prev = cmd;
			cmd = cmd->next;
			s = null_increment(s);
		}
		else
			s = add_arg(cmd, s);
	}
	return (EXIT_SUCCESS);
}

/*Converts the input string s to a linked list and returns head node.*/
t_cmd	*input_to_lst(char *s, t_data *data)
{
	if (s == NULL || *s == 0)
		return (NULL);
	data->cmd_head = create_cmd(data);
	if (split_input(s, data->cmd_head, data) != 0)
	{
		data->exitstatus = ft_error(NULL, NULL, 10);
		free_cmds_error(data->cmd_head);
		return (NULL);
	}
	return (data->cmd_head);
}
