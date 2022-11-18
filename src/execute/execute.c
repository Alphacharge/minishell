/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 09:27:23 by rbetz             #+#    #+#             */
/*   Updated: 2022/11/18 18:43:59 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

// static void	execute_child(int *fds, char *exe, char **envp)
// {
// 	if (var->index_fd == 0)
// 		first_fd(var);
// 	else if (var->index_fd == var->calls - 1)
// 	{
// 		if (dup2(var->fds[var->index_fd - 1][0], 0) < 0
// 		|| dup2(var->fd_out, 1) < 0)
// 			ft_error(var);
// 		close(var->fd_out);
// 	}
// 	else
// 	{
// 		if (dup2(var->fds[var->index_fd - 1][0], 0) < 0
// 		|| dup2(var->fds[var->index_fd][1], 1) < 0)
// 			ft_error(var);
// 		close(var->fds[var->index_fd - 1][0]);
// 		close(var->fds[var->index_fd][1]);
// 	}
// 	execve(exe, var->args[var->index_fd], envp);
// }

// void	executor(t_exec *exec, t_env *env)
// {
// 	pid_t	pid;
	// int		fds[2];
	// (void)exec;
	// (void)env;
	// pipe(fds);
	// pid = fork();
	// if (pid == 0)
	// 	execute_child(fds, exec, create_envp_from_env(env));
	// close(fds[0]);
	// close(fds[1]);
// }

static void	exec_cmd(t_cmd *cmd, t_env *env)
{
	int	pid;

	pid = fork();
	if (pid == 0)
		execve(cmd->argv[0], cmd->argv, create_envp_from_env(env));
	if (pid < 0)
		ft_error("minishell: exec_cmd:");
}

/*If exit is found, exit status is returned. Otherwise return value is -1.*/
int	execute_list(t_cmd *lst, t_env *env)
{
	t_cmd	*current;

	current = lst;
	while (current != NULL)
	{
		if (current->type == 0)
		{
			if (ft_strncmp(lst->argv[0], "cd", 3) == 0)
				cd(lst->argv, env);
		}
		if (current->type == 1)
			exec_cmd(current, env);
		current = current->next;
		waitpid(-1, NULL, 0);
	}
	return (-1);
}
