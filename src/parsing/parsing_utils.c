/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 16:44:46 by fkernbac          #+#    #+#             */
/*   Updated: 2022/12/01 16:59:55 by fkernbac         ###   ########.fr       */
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