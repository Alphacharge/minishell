/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 09:27:23 by rbetz             #+#    #+#             */
/*   Updated: 2022/11/08 17:23:30 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static void	execute_child(t_var *var, char **envp)
{
	if (var->index_fd == 0)
		first_fd(var);
	else if (var->index_fd == var->calls - 1)
	{
		if (dup2(var->fds[var->index_fd - 1][0], 0) < 0
		|| dup2(var->fd_out, 1) < 0)
			ft_error(var);
		close(var->fd_out);
	}
	else
	{
		if (dup2(var->fds[var->index_fd - 1][0], 0) < 0
		|| dup2(var->fds[var->index_fd][1], 1) < 0)
			ft_error(var);
		close(var->fds[var->index_fd - 1][0]);
		close(var->fds[var->index_fd][1]);
	}
	execve(var->exec, var->args[var->index_fd], envp);
}

void	execute_programs(t_var *var, char **envp)
{
	pid_t		pid;

	free(var->args[var->index_fd][0]);
	var->args[var->index_fd][0] = ft_strdup(var->exec);
	pipe(var->fds[var->index_fd]);
	pid = fork();
	if (pid == 0)
		execute_child(var, envp);
	close_fds(var);
	var->here = 0;
	var->index_fd++;
}
