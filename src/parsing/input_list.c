/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humbi <humbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 16:49:45 by fkernbac          #+#    #+#             */
/*   Updated: 2023/01/28 14:53:33 by humbi            ###   ########.fr       */
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
		return (ft_error("malloc", NULL, 1), NULL);
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

/*Creates an empty t_cmd node.*/
static t_cmd	*create_cmd(t_data *data)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (cmd == NULL)
		return (ft_error("malloc", NULL, 1), NULL);
	cmd->argv = NULL;
	cmd->data = data;
	cmd->name = NULL;
	cmd->param = NULL;
	cmd->next = NULL;
	cmd->prev = NULL;
	cmd->redir = NULL;
	cmd->here = false;
	cmd->type = EXEC;
	cmd->fds[0] = FD_UNUSED;
	cmd->fds[1] = FD_UNUSED;
	cmd->reds[0] = FD_UNUSED;
	cmd->reds[1] = FD_UNUSED;
	return (cmd);
}

/*Converts the input string s to a linked list and returns head node.*/
t_cmd	*input_to_lst(char *s, t_data *data)
{
	t_cmd	*head;
	t_cmd	*current;

	if (s == NULL || *s == 0)
		return (NULL);
	head = create_cmd(data);
	current = head;
	while (*s != 0)
	{
		s = null_whitespace(s);
		if (*s == 0)
			break ;
		if (*s == '>' || *s == '<')
		{
			s = new_redir(current, s);
			if (s == NULL)
				return (ft_error(NULL, NULL, 10), free_cmds_error(head));
		}
		else if (*s == '|')
		{
			if (current->name == NULL)
				return (ft_error(NULL, NULL, 10), free_cmds_error(head));
			current->next = create_cmd(data);
			current->next->prev = current;
			current = current->next;
			s = null_increment(s);
		}
		else
			s = add_arg(current, s);
	}
	return (head);
}
