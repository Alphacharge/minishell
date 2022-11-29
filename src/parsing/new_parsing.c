/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 16:50:07 by fkernbac          #+#    #+#             */
/*   Updated: 2022/11/29 14:00:56 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*
Concept:

<<file echo hello$HOME>test|"c"a"t" -e

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
printf("n_w skipped to %s\n", s);
	return (s);
}

/*Increments string by one and replaces skipped value with \0.*/
char	*null_increment(char *s)
{
	*s = '\0';
	s++;
	return (s);
}

static void	append_redir(t_cmd *cmd, t_redir *r)
{
	t_redir	*current;

printf("append_redir\n");
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

static char	*add_redir(t_cmd *cmd, char *s)
{
	t_redir	*r;

printf("add_redir\n");
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
			r->r_type = A_INPUT;
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

/*Creates an empty t_cmd node.*/
t_cmd	*create_cmd(t_env *env)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (cmd == NULL)
		return (ft_error("minishell:create_cmd: malloc error"), NULL);
	cmd->argv = NULL;
	cmd->env = env;
	cmd->name = NULL;
	cmd->param = NULL;
	cmd->pipe = NULL;
	cmd->redir = NULL;
	cmd->type = EXEC;
	return (cmd);
}

static t_cmd	*input_to_lst(char *s, t_env *env)
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

char	*skip_single_quotes(char *s)
{
	s++;
	while (*s != 0 && *s != '\'')
		s++;
	if (*s == '\'')
		s++;
	return (s);
}

char	*skip_to_envvar(char *s)
{
	while (*s != 0 && *s != '$')
	{
		if (*s == '\'')
			s = skip_single_quotes(s);
		s++;
	}
	return (s);
}

int	count_var_strings(char *s)
{
	int	n;

	n = 0;
	while (*s != '\0')
	{
		n++;
		s = skip_to_envvar(s);
		if (*s == '$')
			n++;
	}
	return (n);
}

char	*alloc_var_name(char *s)
{
	int	l;
	int	i;
	char	*name;

	l = 0;
	i = 0;
	while (s[l] != '\0' && (ft_isalnum(s[l]) == 1 || s[l] == '_'))
		l++;
	name = ft_calloc(l + 1, sizeof(char));
	if (name == NULL)
		return (NULL);
	while (i <= l)
	{
		name[i] = s[i];
		i++;
	}
	name[i] = '\0';
	return (name);
}

char	*expand_envvars(char *s, t_env *env)
{
	char	**array;
	char	*joined;
	int		envvars;
	int		i;

	i = 0;
	joined = NULL;
	envvars = count_var_strings(s);
printf("counted %i envvar strings\n", envvars);
	if (envvars == 0)
		return (s);
	array = ft_calloc(envvars, sizeof (char *));
	if (array == NULL)
		return (NULL);
	while (*s != 0)
	{
		array[i] = s;
//need to allocate every string;
		s = skip_to_envvar(s);
printf("skipped to %s\n", s);
		if (*s == '$')
		{
			s = null_increment(s);
			i++;
			array[i] = get_env_var(env, alloc_var_name(s));
		}
		i++;
	}
	joined = array[0];
	i = 1;
	while (i < envvars)
	{
printf("joining %s and %s\n", joined, array[i]);
		joined = ft_strjoin(joined, array[i]);
		i++;
	}
	return (joined);
}

int	count_parameters(t_cmd *cmd)
{
	t_param	*current;
	int	n;

	current = cmd->param;
	n = 0;
	while (current != NULL)
	{
		n++;
		current = current->next;
	}
	return (n);
}

char	**create_argv(t_cmd *cmd, t_env *env)
{
	char	**argv;
	t_param	*current;
	int		i;

	i = 1;
	(void)env;
	current = cmd->param;
printf("allocating %i args\n", count_parameters(cmd) + 2);
	argv = ft_calloc(count_parameters(cmd) + 2, sizeof(char *));
	if (argv == NULL)
		return (NULL);
	//PATH not inserted yet!
	argv[0] = cmd->name;
	while (current != NULL)
	{
		// argv[i] = expand_envvars(current->arg, env);
		// argv[i] = remove_quotes(argv[i]);
		current = current->next;
	}
	argv[i] = NULL;
	return (argv);
}

/*Allocates cleaned up argv array for use in execve.*/
void	add_argvs(t_cmd *current, t_env *env)
{
	//this function needs to expand all variables and to remove all quotes
	//variables have to be expanded before quotes are removed
	while (current != NULL)
	{
		//can there be a variable in name?
		current->argv = create_argv(current, env);
		current = current->pipe;
	}
}

t_cmd	*parse(char *s, t_env *env)
{
	t_cmd	*lst;

//seems to be working; check any combination of quotes
	lst = input_to_lst(s, env);
//cleans up and reallocates every string: double free could happen otherwise.
	add_argvs(lst, env);
	// create argv;
	return (lst);
}
