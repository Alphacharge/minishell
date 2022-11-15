/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:23:19 by fkernbac          #+#    #+#             */
/*   Updated: 2022/11/15 14:48:11 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "errorhandling.h"

//Returns index of next token. Placeholder.
// static int	is_token(char *s)
// {
// 	if (s[0] == '\'' || s[0] == '\"' || s[0] == '<' || s[0] == '>' || s[0] == '&' || s[0] == '|' || s[0] == '$')
// 		return (1);
// 	return (0);
// }

/*Returns type macro of given command.*/
static int	check_type(char *s)
{
	if (s[0] == 'c' && s[1] == 'd')
		return (BLTIN);
	if (s[0] == 'e' && s[1] == 'x' && s[2] == 'i' && s[3] == 't' && s[4] == '\0')
		return (BLTIN);
	return (-1);
}

static char	**create_argv(char **array, int start)
{
	int		words;
	int		i;
	char	**argv;

	words = 0;
	i = 0;
	argv = NULL;
	argv = ft_calloc(2, sizeof(char *));
	if (VERBOSE == 1)
		printf("create_argv: starting at %s\n", array[start]);
	argv[0] = array[start];
	argv[1] = NULL;
	// while (s + words != NULL && is_token(s + words) == 0)
	// 	words++;
	// argv = ft_calloc(words, sizeof(char *));
	// if (argv == NULL)
	// 	return (ft_error("minishell: create_argv:"), NULL);
	// while (i < words)
	// {
	// 	argv[i] = s + i;
	// 	i++;
	// }
	// argv[i] = NULL;
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
	if (VERBOSE == 1)
		printf("create_list parameter: [0] %s | [1] %s\n", args[0], args[1]);
	while (args[i] != NULL)
	{
		if (VERBOSE == 1)
			printf("create_list: allocating node for %s\n", args[i]);
		cmd = ft_calloc(1, sizeof(t_cmd));
		if (cmd == NULL)
			return (ft_error("minishell:create_list"), NULL);
		if (prev != NULL)
			prev->next = cmd;
		cmd->argv = create_argv(args, i);
		if (cmd->argv == NULL)
			return (free_cmds(head), NULL);
		cmd->type = check_type(args[i]);
		cmd->next = NULL;
		prev = cmd;
		if (head == NULL)
			head = cmd;
		i++;
	}
	if (VERBOSE == 1)
		printf("create_list created %i nodes\n", i);
	return (head);
}
