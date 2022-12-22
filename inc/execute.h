/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 09:27:46 by rbetz             #+#    #+#             */
/*   Updated: 2022/12/22 17:54:11 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include <stdlib.h> 		// malloc, free, exit
# include <unistd.h> 		// close,read,write,dup2, access, fork, pipe, execve
# include <stdio.h> 		// printf
# include <sys/wait.h>		// waitpid
# include "structs.h"
# include "errorhandling.h"
# include "environment.h"
# include "execute.h"
# include "builtins.h"
# include "utils.h"
# include "redirects.h"

// void	executor(t_exec *exec, t_env *env);
int		execute_list(t_cmd *lst, t_prompt *prompt);
void	dup_pipe_fds(t_cmd *cmd);
void	dup_reds_fds(t_cmd *cmd);
void	close_pipe_fds(t_cmd *cmd);
void	close_reds_fds(t_cmd *cmd);
void	close_piping(t_cmd *cmd);
void	close_and_neg(int *fd);
#endif
