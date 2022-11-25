/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 09:27:23 by rbetz             #+#    #+#             */
/*   Updated: 2022/11/25 10:42:56 by rbetz            ###   ########.fr       */
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
	int	ret;

	pid = fork();
	if (pid == 0)
		execve(cmd->argv[0], cmd->argv, create_envp_from_env(env));
	if (pid < 0)
		ft_error("minishell: exec_cmd:");
	waitpid(-1, &ret, 0);
	if (ret < 0)
		ft_error(cmd->argv[0]);
}

int	exec_builtin(t_cmd *cmd, t_env *env)
{
	if (cmd->argv[0][0] == 'c')
		cd(cmd->argv, env);
	else if (cmd->argv[0][0] == 'p')
		pwd(arraycount(cmd->argv), cmd->argv);
	// else if (cmd->argv[0][0] == 'u')
	// 	unset(arraycount(cmd->argv), cmd->argv, env);
	else if (ft_strcmp(cmd->argv[0], "echo") == 0)
		echo(arraycount(cmd->argv), cmd->argv);
	else if (ft_strcmp(cmd->argv[0], "env") == 0)
		print_env(env, 1);
	else if (ft_strcmp(cmd->argv[0], "exit") == 0)
		return (shell_exit(cmd->argv));
	// else if (strcmp(cmd->argv[0], "export") == 0)
	// 	export(arraycount(cmd->argv), cmd->argv, env);
	return (-1);
}

/*If exit is found, exit status is returned. Otherwise return value is -1.*/
int	execute_list(t_cmd *lst, t_env **env)
{
	t_cmd	*current;
	int		ret;

	current = lst;
	ret = -1;
	//commands are executed one after another; needs to be changed to pipe
	while (current != NULL)
	{
		if (current->type == 0)
		{
			if (lst->argv[0][0] == 'c')
				cd(lst->argv, *env);
			else if (lst->argv[0][0] == 'p')
				pwd(arraycount(lst->argv), lst->argv);
			else if (lst->argv[0][0] == 'u')
				*env = unset(arraycount(lst->argv), lst->argv, *env);
			else if (strcmp(lst->argv[0], "echo") == 0)
				echo(arraycount(lst->argv), lst->argv);
			else if (strcmp(lst->argv[0], "export") == 0)
				*env = export(arraycount(lst->argv), lst->argv, *env);
			else if (strcmp(lst->argv[0], "env") == 0)
				print_env(*env, 1);
			else if (strcmp(lst->argv[0], "exit") == 0)
				return (shell_exit(lst->argv));
			// else if (strcmp(lst->argv[0], "export") == 0)
				// export(arraycount(lst->argv), lst->argv, env);
		}
		if (current->type == 1)
			exec_cmd(current, *env);
		current = current->next;
	}
	return (ret);
}
