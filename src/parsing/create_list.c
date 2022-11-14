/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:23:19 by fkernbac          #+#    #+#             */
/*   Updated: 2022/11/14 12:45:53 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

//Returns index of next token. Placeholder.
static int	is_token(char *s)
{
	if (s[0] == '\'' || s[0] == '\"' || s[0] == '<' || s[0] == '>' || s[0] == '&' || s[0] == '|' || s[0] == '$')
		return (1);
	return (0);
}

/*Returns type macro of given command.*/
static int	check_type(char *s)
{
	if (s[0] == 'c' && s[1] == 'd')
		return (BLTIN);
	if (s[0] == 'e' && s[1] == 'x' && s[2] == 'i' && s[3] == 't' && s[4] == '\0')
		return (BLTIN);
	return (-1);
}

static char	**create_argv(char *command)
{
	int		words;
	int		i;
	char	**argv;

	words = 0;
	i = 0;
	argv = NULL;
	while (command + words != NULL && is_token(command + words) == 0)
		words++;
	argv = ft_calloc(words, sizeof(char *));
	if (argv == NULL)
		return (ft_error("minishell: create_argv:"), NULL);
	while (i < words)
	{
		argv[i] = command + i;
		i++;
	}
	argv[i] = NULL;
	return (argv);
}

t_cmd	*create_list(char **args)
{
	int		i;
	t_cmd	*head;
	t_cmd	*cmd;
	t_cmd	*prev;

	i = 0;
	head = NULL;
	cmd = NULL;
	prev = NULL;
	if (args == NULL)
		return (0);
	while (args[i] != NULL)
	{
		cmd = ft_calloc(1, sizeof(t_cmd));
		if (cmd == NULL)
			return (ft_error("minishell:create_list"), NULL);
		if (prev != NULL)
			prev->next = cmd;
//here we need to allocate a NULL-terminated string array for execve
		cmd->argv = create_argv(args[i]);
		if (cmd->argv == NULL)
			return (free_cmds(head), NULL);
		cmd->type = check_type(args[i]);
		printf("%s\n", cmd->argv[1]);
		cmd->next = NULL;
		prev = cmd;
		if (head == NULL)
			head = cmd;
		i++;
	}
	if (VERBOSE == 1)
		printf("created %i nodes\n", i);
	return (head);
}
