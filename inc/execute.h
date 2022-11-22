/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 09:27:46 by rbetz             #+#    #+#             */
/*   Updated: 2022/11/22 16:10:18 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include <stdlib.h> // malloc, free, exit
# include <unistd.h> // close, read, write, dup2, access, fork, pipe, execve
# include <stdio.h> // printf
# include "structs.h"
# include "errorhandling.h"
# include "filedescriptors.h"
# include "environment.h"
# include "execute.h"
# include "builtins.h"
# include "utils.h"

// void	executor(t_exec *exec, t_env *env);
int		execute_list(t_cmd *lst, t_env *env);

#endif
