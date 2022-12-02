/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 16:44:46 by fkernbac          #+#    #+#             */
/*   Updated: 2022/12/02 22:34:11 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*Increments string by one and replaces skipped value with \0.*/
char	*null_increment(char *s)
{
	*s = '\0';
	s++;
	return (s);
}

//not sure if this value is actually needed
void	set_type(t_cmd *cmd)
{
	if (ft_strcmp("cd", cmd->name) == 0 || \
		ft_strcmp("echo", cmd->name) == 0 || \
		ft_strcmp("env", cmd->name) == 0 || \
		ft_strcmp("exit", cmd->name) == 0 || \
		ft_strcmp("export", cmd->name) == 0 || \
		ft_strcmp("pwd", cmd->name) == 0 || \
		ft_strcmp("unset", cmd->name) == 0)
		cmd->type = BLTIN;
	else
		cmd->type = EXEC;
}

/*Counts the number of t_param nodes connected to cmd.*/
int	count_parameters(t_cmd *cmd)
{
	t_param	*current;
	int		n;

	current = cmd->param;
	n = 0;
	while (current != NULL)
	{
		n++;
		current = current->next;
	}
	return (n);
}

/*Checks for shell tokens but not for quotation marks.*/
int	is_token(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

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
