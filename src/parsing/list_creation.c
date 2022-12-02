/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_creation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 16:49:45 by fkernbac          #+#    #+#             */
/*   Updated: 2022/12/02 16:23:33 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*Skips all consecutive whitespace characters and sets them to \0.
Returns pointer to next non-whitespace character.*/
char	*null_whitespace(char *s)
{
	if (s == NULL || *s == 0)
		return (s);
	while (ft_isspace(*s) == 1)
	{
		*s = 0;
		s++;
	}
	return (s);
}

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
static char	*add_redir(t_cmd *cmd, char *s)
{
	t_redir	*r;

	if (cmd == NULL)
		return (NULL);
	r = ft_calloc(1, sizeof(t_redir));
	if (r == NULL)
		return (ft_error("minishell: add_redir: malloc error"), NULL);
	r->next = NULL;
	if (*s == '<')
	{
		s = null_increment(s);
		if (*s == '<')
		{
			s = null_increment(s);
			r->r_type = HERE;
		}
		else
			r->r_type = INPUT;
	}
	else if (*s == '>')
	{
		s = null_increment(s);
		if (*s == '>')
		{
			s = null_increment(s);
			r->r_type = A_OUTPUT;
		}
		else
			r->r_type = OUTPUT;
	}
	s = skip_space(s);
	r->file = s;
	s = skip_argument(s);
	append_redir(cmd, r);
	return (s);
}

/*Adds string as next parameter or as command name if no command is set yet.*/
char	*add_arg(t_cmd *cmd, char *s)
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

/*inits the array of filedescriptors*/
static void	init_fds(int *fds)
{
	int	i;

	i = 3;
	fds[0] = 0;
	fds[1] = 1;
	fds[2] = 2;
	while (i < 10)
		fds[i++] = -1;
}

/*Creates an empty t_cmd node.*/
t_cmd	*create_cmd(t_env *env)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (cmd == NULL)
		return (ft_error("minishell:create_cmd: malloc error"), NULL);
	cmd->argv = NULL;
	init_fds(cmd->fds);
	cmd->env = env;
	cmd->name = NULL;
	cmd->param = NULL;
	cmd->pipe = NULL;
	cmd->redir = NULL;
	cmd->type = EXEC;
	return (cmd);
}

/*Converts the input string s to a linked list and returns head node.*/
t_cmd	*input_to_lst(char *s, t_env *env)
{
	t_cmd	*head;
	t_cmd	*current;

	if (s == NULL || *s == 0)
		return (NULL);
	head = create_cmd(env);
	current = head;
	while (*s != 0)
	{
		s = null_whitespace(s);
		if (*s == 0)
			break ;
		if (*s == '>' || *s == '<')
			s = add_redir(current, s);
		else if (*s == '|')
		{
			current->pipe = create_cmd(env);
			current = current->pipe;
			s = null_increment(s);
		}
		else
			s = add_arg(current, s);
	}
	return (head);
}
