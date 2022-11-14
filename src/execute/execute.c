/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 09:27:23 by rbetz             #+#    #+#             */
/*   Updated: 2022/11/14 17:58:31 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "structs.h"

// static void	execute_child(t_var *var, char **envp)
// {
// 	if (var->index_fd == 0)
// 		first_fd(var);
// 	else if (var->index_fd == var->calls - 1)
// 	{
// 		if (dup2(var->fds[var->index_fd - 1][0], 0) < 0
// 		|| dup2(var->fd_out, 1) < 0)
// 			ft_error(NULL);
// 		close(var->fd_out);
// 	}
// 	else
// 	{
// 		if (dup2(var->fds[var->index_fd - 1][0], 0) < 0
// 		|| dup2(var->fds[var->index_fd][1], 1) < 0)
// 			ft_error(NULL);
// 		close(var->fds[var->index_fd - 1][0]);
// 		close(var->fds[var->index_fd][1]);
// 	}
// 	execve(var->exec, var->args[var->index_fd], envp);
// }

// void	execute_programs(t_var *var, char **envp)
// {
// 	pid_t		pid;

// 	free(var->args[var->index_fd][0]);
// 	var->args[var->index_fd][0] = ft_strdup(var->exec);
// 	pipe(var->fds[var->index_fd]);
// 	pid = fork();
// 	if (pid == 0)
// 		execute_child(var, envp);
// 	close_fds(var);
// 	var->here = 0;
// 	var->index_fd++;
// }

/*Placeholder function for executing a linked list of commands.*/
int	execute(t_cmd *cmd_head)
{
	t_cmd	*current;

	current = cmd_head;
	while (current != NULL)
	{
		if (ft_strncmp(current->argv[0], "cd", 2) == 0)
			builtin_cd(current);
		else if (ft_strncmp(current->argv[0], "exit", 4) == 0)
			return (builtin_exit(current));
//here any other program will be executed
		// else
		// 	execve(current->argv[0], current->argv, getenv());
		current = current->next;
	}
	return (0);
}
