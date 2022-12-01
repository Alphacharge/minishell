/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 16:50:07 by fkernbac          #+#    #+#             */
/*   Updated: 2022/12/01 17:05:40 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*
Concept:

1. create list of t_cmd with properties redir, param and pipe (= next)
save only pointers to input string
replace every whitespace, redir and pipe with 0

2. expand variables

3. remove quotes, clean up strings
*/

/*Allocates cleaned up argv array for use in execve.*/
int	add_argvs(t_cmd *current, t_env *env)
{
	//this function needs to expand all variables and to remove all quotes
	//variables have to be expanded before quotes are removed
	while (current != NULL)
	{
		//can there be a variable in name?
		set_type(current);
		current->argv = create_argv(current, env);
		if (current->argv == NULL)
			return (1);
		current = current->pipe;
	}
	return (0);
}

t_cmd	*parse(char *s, t_env *env)
{
	t_cmd	*lst;

//seems to be working; check any combination of quotes
	lst = input_to_lst(s, env);
//cleans up and reallocates every string: double free could happen otherwise.
	if (add_argvs(lst, env) == 1)
		return (free_cmds(lst), NULL);
	// create argv;
	return (lst);
}
