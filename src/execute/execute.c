/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 09:27:23 by rbetz             #+#    #+#             */
/*   Updated: 2022/11/14 10:55:04 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static void	execute_child(int *fds, char *exe, char **envp)
{
	if (var->index_fd == 0)
		first_fd(var);
	else if (var->index_fd == var->calls - 1)
	{
		if (dup2(var->fds[var->index_fd - 1][0], 0) < 0
		|| dup2(var->fd_out, 1) < 0)
			ft_error(var, 9);
		close(var->fd_out);
	}
	else
	{
		if (dup2(var->fds[var->index_fd - 1][0], 0) < 0
		|| dup2(var->fds[var->index_fd][1], 1) < 0)
			ft_error(var, 9);
		close(var->fds[var->index_fd - 1][0]);
		close(var->fds[var->index_fd][1]);
	}
	execve(exe, var->args[var->index_fd], envp);
}

void	execute_programs(t_exec *exec, t_env *env)
{
	pid_t	pid;
	int		fds[2];

	pipe(fds);
	pid = fork();
	if (pid == 0)
		execute_child(fds, exec, create_envp_from_env(env));
	close(fds[0]);
	close(fds[1]);
}
