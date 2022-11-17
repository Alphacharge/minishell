/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_to_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:20:54 by fkernbac          #+#    #+#             */
/*   Updated: 2022/11/17 17:31:02 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

//  ls -l     -a|"c"a"t" -e

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
	printf("arg_len: counted length |%i|\n", i - quotations);
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
	if (VERBOSE == 1)
		printf("input_to_arg: allocated argument |%s|\n", arg);
	return (arg);
}

/*Skips one argument containing any amount of quotation marks.*/
char	*skip_argument(char *s)
{
	while (s[0] != '\0' && ft_isspace(s[0]) == 0)
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
		if (is_token(s[0]) == 1)
			break ;
		args++;
		s = skip_argument(s);
	}
	if (VERBOSE == 1)
		printf("count_args: counted %i\n", args);
	return (args);
}

/*Creates an array of strings until null byte or token is encountered.*/
static char	**create_argv(char *s, t_env *env)
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
		if (i == 0)
			argv[0] = get_path(get_path_var(env), argv[0]);
		if (VERBOSE == 1)
			printf("argv[0]: |%s|\n", argv[0]);
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

	cmd = NULL;
	if (s == NULL || s[0] == '\0')
		return (NULL);
	s = skip_space(s);
	cmd = ft_calloc(1, sizeof(t_cmd));
	if (cmd == NULL)
		return (NULL);
	cmd->argv = create_argv(s, env);
	if (cmd->argv == NULL)
		return (NULL);
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
		while (input[0] != '\0' && is_token(input[0]) == 0)
			input++;
		if (is_token(input[0]) == 1)
			input++;
		if (VERBOSE == 1)
			printf("str_to_lst: created node for |%s|\n", cmd->argv[0]);
	}
	return (head);
}
