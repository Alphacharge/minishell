/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_to_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:20:54 by fkernbac          #+#    #+#             */
/*   Updated: 2022/11/23 13:49:18 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
//  ls -l     -a|"c"a"t" -e

//FIX THIS FUNCTION

/*Skips one argument containing any amount of quotation marks.*/
char	*skip_argument(char *s)
{
	while (s[0] != '\0' && ft_isspace(s[0]) == 0 && is_token(s[0]) == 0)
	{
		if (s[0] == '\"')
		{
			s++;
			while (s[0] != '\0' && s[0] != '\"')
				s++;
		}
		if (s[0] == '\'')
		{
			s++;
			while (s[0] != '\0' && s[0] != '\'')
				s++;
		}
		s = skip_word(s);
	}
	return (s);
}

static char	*skip_to_pipe(char *s)
{
	while (s[0] != '\0' && s[0] != '|')
		s++;
	return (s);
}

/*Counts length until next space or token and subtracts number of found
quotation marks.*/
static int	arg_len(char *s)
{
	int	i;
	int	quotations;

	i = 0;
	quotations = 0;
	while (s[i] != '\0' && ft_isspace(s[i]) == 0 && is_token(s[i]) == 0)
	{
		if (s[i] == '\"')
		{
			i++;
			quotations++;
			while (s[i] != '\0' && s[i] != '\"')
				i++;
			if (s[i] == '\"')
				quotations++;
		}
		i++;
	}
	return (i - quotations);
}

static char	*input_to_arg(char *s)
{
	int		i;
	int		j;
	int		len;
	char	*arg;

	i = 0;
	j = 0;
	if (s == NULL || s[0] == '\0')
		return (NULL);
	len = arg_len(s);
	arg = ft_calloc(len + 1, sizeof(char));
	if (arg == NULL)
		return (NULL);
	while (j < len)
	{
		if (s[i] == '\"')
			i++;
		arg[j] = s[i];
		i++;
		j++;
	}
	arg[len] = '\0';
	return (arg);
}

//exit, cd check
static void	set_type(t_cmd *cmd)
{
	if (ft_strncmp("exit", cmd->argv[0], 5) == 0)
		cmd->type = BLTIN;
	else if (ft_strncmp("cd", cmd->argv[0], 3) == 0)
		cmd->type = BLTIN;
	else
		cmd->type = EXEC;
}

//2>&1
/*Returns number of arguments until next token. Quotation marks are handled.*/
static int	count_args(char *s)
{
	int	args;

	args = 0;
	while (s[0] != '\0' && s[0] != '|')
	{
		s = skip_space(s);
		if (s[0] != '\0' && is_token(s[0]) == 0)
			args++;
		s = skip_argument(s);
		s = skip_space(s);
		if (s[0] == '>')
		{
			s++;
			if (s[0] == '>')
				s++;
			s = skip_space(s);
			if (s[0] == '\0' || is_token(s[0]) == 1)
				return (printf("minishell: syntax error near unexpected token '%c'\n", s[0]), -1);
			s = skip_argument(s);
			s = skip_space(s);
		}
	}
	return (args);
}

char	*add_redir(char *s, t_cmd *cmd)
{
	t_redir	*current;

	current = cmd->redir;
	if (s[0] == '>')
		s++;
	if (s[0] == '>')
		s++;
	s = skip_space(s);
	if (current == NULL)
	{
		cmd->redir = ft_calloc(1, sizeof(t_redir));
		cmd->redir->file = get_word(s);
		cmd->redir->next = NULL;
	}
	else
	{
		while (current->next != NULL)
			current = current->next;
		current->next = ft_calloc(1, sizeof(t_redir));
		current->next->file = get_word(s);
		current->next->next = NULL;
	}
	s = skip_word(s);
	s = skip_space(s);
	return (s);
}

/*Creates an array of strings until null byte or token is encountered.*/
static char	**create_argv(char *s, t_cmd *cmd)
{
	char	**argv;
	int		nr;
	int		i;

	i = 0;
	nr = count_args(s);
	if (nr < 0)
		return (NULL);
	argv = ft_calloc(nr + 1, sizeof(char *));
	if (argv == NULL)
		return (NULL);
	while (i < nr)
	{
		s = skip_space(s);
		argv[i] = input_to_arg(s);
		if (argv[i] == NULL)
			return (free_ptr_array((void **)argv), NULL);
		i++;
		s = skip_argument(s);
		s = skip_space(s);
		while (s[0] == '>' || s[0] == '<')
			s = add_redir(s, cmd);
	}
	argv[i] = NULL;
	return (argv);
}

/*Skips spaces and allocates next node with argv until next token.*/
static t_cmd	*create_node(char *s, t_env *env)
{
	t_cmd	*cmd;
	char	**paths;
	char	*cmd_name;

	cmd = NULL;
	paths = NULL;
	cmd_name = NULL;
	if (s == NULL || s[0] == '\0')
		return (NULL);
	s = skip_space(s);
	cmd = ft_calloc(1, sizeof(t_cmd));
	if (cmd == NULL)
		return (NULL);
	cmd->env = env;
	cmd->pipe = NULL;
	cmd->redir = NULL;
	cmd->argv = create_argv(s, cmd);
	if (cmd->argv == NULL)
		return (NULL);
	set_type(cmd);
	if (cmd->type == EXEC)
	{
		cmd_name = cmd->argv[0];
		paths = get_path_var(env);
		cmd->argv[0] = get_path(paths, cmd->argv[0]);
		free_ptr_array((void **)paths);
		if (cmd->argv[0] == NULL)
		{
			printf("minishell: %s: command not found\n", cmd_name);
			cmd->argv[0] = cmd_name;
			free_ptr_array((void **)cmd->argv);
			cmd_name = NULL;
			cmd = ft_free(cmd);
		}
		ft_free(cmd_name);
	}
	return (cmd);
}

//problems: stuck if there is no space between command and token
//ls -la|cat -e
t_cmd	*str_to_lst(char *input, t_env *env)
{
	t_cmd	*head;
	t_cmd	*cmd;
	t_cmd	*prev;

	head = NULL;
	cmd = NULL;
	prev = NULL;
	input = skip_space(input);
	while (input[0] != '\0')
	{
		cmd = create_node(input, env);
		if (cmd == NULL)
			break ;
		if (head == NULL)
			head = cmd;
		if (prev != NULL)
			prev->pipe = cmd;
		prev = cmd;
		//if we implement & the whole logic of this loop needs to be changed
		input = skip_to_pipe(input);
		if (input[0] == '\0')
			break ;
		//any other token will be handled as argument
		else if (input[0] == '|')
			input++;
	}
	return (head);
}
