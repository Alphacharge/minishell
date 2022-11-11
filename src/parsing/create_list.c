/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:23:19 by fkernbac          #+#    #+#             */
/*   Updated: 2022/11/11 14:15:31 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	check_type(char *s)
{
	if (s[0] == 'c' && s[1] == 'd')
		return (BLTIN);
	if (s[0] == 'e' && s[1] == 'x' && s[2] == 'i' && s[3] == 't' && s[4] == '\0')
		return (BLTIN);
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
			return (ft_error("minishell:create_list"), 1);
		if (prev != NULL)
			prev->next = cmd;
		cmd->arg = args[i];
		cmd->type = check_type(cmd->arg);
		cmd->next = NULL;
		prev = cmd;
		if (head == NULL)
			head = cmd;
		i++;
	}
	return (head);
}
