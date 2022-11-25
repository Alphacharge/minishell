/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 16:50:07 by fkernbac          #+#    #+#             */
/*   Updated: 2022/11/25 17:40:12 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*
Concept:

echo hello$HOME>test|"c"a"t" -e

1. saving input into linked list

new struct: input
input->text -> allocated null terminated string
input->type -> command/parameter/redirection/pipe
input->next -> next input struct

input->text = echo
input->type = command

input->text = hello$Home
input->type = parameter

input->text = test
input->type = redirection

input->text = NULL
input->type = pipe

input->text = "c"a"t"
input->type = command

input->text = -e
input->type = parameter

4. set up command struct. search for pipes.
echo_cmd->pipe = cat_cmd

2. expand variables
input->text = hello/usr/fkernbac
free(old)

insert redirections
echo_cmd->redir->file = test

3. remove quotes
input->text = cat
free(old)

5.

*/

/*
Concept:

1. create list of t_cmd with properties redir, param and pipe (= next)
save only pointers to input string
replace every whitespace, redir and pipe with 0

2. expand variables

3. remove quotes, clean up strings
*/

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

/*Increments string by one and replaces skipped value with \0.*/
char	*null_incerement(char *s)
{
	s = '\0';
	s++;
	return (s);
}

static void	append_redir(t_cmd *cmd, t_redir *r)
{
	t_redir	*current;

	current = cmd->redir;
	if (current == NULL)
	{
		cmd->redir = r;
		return 
	}
	while (current != NULL && current->next != NULL)
		current = current->next;

}

static char	*add_redir(t_cmd *cmd, char *s)
{
	t_redir	*r;

	if (cmd == NULL)
		return (NULL);
	r = ft_calloc(1, sizeof(t_redir));
	if (r == NULL)
		return (ft_error("minishell: add_redir: malloc error"), NULL);
	if (*s == '<')
	{
		s = null_increment(s);
		if (*s == '<')
		{
			s = null_incerement(s);
			r->r_type = A_INPUT;
		}
		else
			r->r_type = INPUT;
	}
	else if (*s == '>')
	{
		s = null_incerement(s);
		if (*s == '>')
		{
			s = null_incerement(s);
			r->r_type = A_OUTPUT;
		}
		else
			r->r_type = OUTPUT;
	}
	r->file = s;
	s = skip_word(s);
	append_redir(cmd, r);
	return (s);
}


t_para	*create_para()
{
			lst->next = ft_calloc();
			lst = lst->next;
			lst->type = PARA;
			lst->string = s;
			//go to next whitespace > < |
			//needs to handle "" and ''
			s = skip_word();

}

t_cmd	*create_cmd(char *s, t_env *env)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(cmd));
	if (cmd == NULL)
		return (ft_error("minishell:create_cmd: malloc error"), NULL);
	cmd->argv = NULL;
	cmd->env = env;
	cmd->param = NULL;
	cmd->pipe = NULL;
	cmd->redir = NULL;
	cmd->type = EXEC;
	if (s == NULL || *s == 0)
		return (cmd->name = NULL, cmd);
	cmd->name = s;
	return (cmd);

			*s = 0;
			s++;
			s = skip_and_null_space();
			lst->next = ft_calloc();
			lst = lst->next;
			lst->type = CMD;
			lst->string = s;
			//go to next whitespace > < |
			//needs to handle "" and ''
			s = skip_word();
}

static t_cmd	*input_to_lst(char *s, t_env *env)
{
	t_cmd	*head;
	t_cmd	*current;

	if (s == NULL || *s == 0)
		return (NULL);
	head = create_cmd(NULL, env);
	current = head;
	while (*s != 0)
	{
		s = null_whitespace(s);
		if (*s == '>' || *s == '<')
			add_redir(current, s);
		else if (*s == '|')
		{
			current->pipe = create_cmd(s, env);
			current = current->pipe;
			*s = 0;
			s++;
		}
		else
			add_arg(current, s);
	}
	return (head);
}

t_cmd	*parse(char *s, t_env *env)
{
	t_cmd	*lst;

	lst = input_to_lst(s, env);
	insert_envvars(lst);
	remove_quotes(lst);
	return (lst);
}
