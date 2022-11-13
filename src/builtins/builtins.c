/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 16:12:55 by fkernbac          #+#    #+#             */
/*   Updated: 2022/11/13 19:44:59 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

//Placeholder. Can be extended or removed if needed.
int	builtin_exit(t_cmd *cmd)
{
	printf("exit\n");
//insert argument handling
//PLACEHOLDER
	if (cmd->argv == NULL)
		return (1);
	return (0);
}

//    argv is an array of pointers to strings passed to the new program
//    as its command-line arguments.  By convention, the first of these
//    strings (i.e., argv[0]) should contain the filename associated
//    with the file being executed.  The argv array must be terminated
//    by a NULL pointer.  (Thus, in the new program, argv[argc] will be
//    NULL.)
int	builtin_cd(t_cmd *cmd)
{
	if (chdir(cmd->argv[1]) != 0)
		return (ft_error("minishell:cd"), 1);
	return (0);
}
