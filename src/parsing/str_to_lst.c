/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_to_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:20:54 by fkernbac          #+#    #+#             */
/*   Updated: 2022/11/24 11:12:40 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

//  ls -l     -a|"c"a"t" -e

static char	*skip_to_token(char *s)
{
	while (s[0] != '\0' && is_token(s[0]) == 0)
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

/*Returns number of arguments until next token. Quotation marks are handled.*/
static int	count_args(char *s)
{
	int	args;

	args = 0;
	while (s[0] != '\0' && is_token(s[0]) == 0)
	{
		s = skip_space(s);
		if (s[0] == '\0' || is_token(s[0]) == 1)
			break ;
		args++;
		s = skip_argument(s);
	}
	return (args);
}

//exit, cd check
static void	set_type(t_cmd *cmd)
{
	if (ft_strcmp("exit", cmd->argv[0]) == 0)
		cmd->type = BLTIN;
	else if (ft_strncmp("cd", cmd->argv[0], 3) == 0)
		cmd->type = BLTIN;
	else if (ft_strcmp("unset", cmd->argv[0]) == 0)
		cmd->type = BLTIN;
	else if (ft_strcmp("env", cmd->argv[0]) == 0)
		cmd->type = BLTIN;
	else if (ft_strcmp("export", cmd->argv[0]) == 0)
		cmd->type = BLTIN;
	else
		cmd->type = EXEC;
}

/*Creates an array of strings until null byte or token is encountered.*/
static char	**create_argv(char *s)
{
	char	**argv;
	int		nr;
	int		i;

	i = 0;
	nr = count_args(s);
	argv = ft_calloc(nr + 1, sizeof(char *));
	if (argv == NULL)
		return (NULL);
	while (i < nr)
	{
		s = skip_space(s);
		argv[i] = input_to_arg(s);
		i++;
		s = skip_argument(s);
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
	cmd->argv = create_argv(s);
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
			cmd_name = free_ptr_array((void **)cmd->argv);
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
		if (prev != NULL)
			prev->next = cmd;
		if (head == NULL)
			head = cmd;
		cmd->next = NULL;
		prev = cmd;
		input = skip_to_token(input);
		if (input[0] == '\0')
			break ;
		//needs extra rules for special tokens
		cmd->operator = input[0];
		while (is_token(input[0]) == 1)
			input++;
	}
	return (head);
}
