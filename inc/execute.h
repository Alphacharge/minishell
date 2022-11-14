/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 09:27:46 by rbetz             #+#    #+#             */
/*   Updated: 2022/11/14 12:35:17 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include <stdlib.h> // malloc, free, exit
# include <unistd.h> // close, read, write, dup2, access, fork, pipe, execve
# include <stdio.h> // printf
# include "structs.h"
# include "libft.h"
// # include "errorhandling.h"
// # include "filedescriptors.h"
# include "builtins.h"
// # include "minishell.h"

// void	execute_programs(t_var *var, char **envp);
int		execute(t_cmd *cmd_head);

#endif
