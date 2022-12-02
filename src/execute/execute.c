/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 09:27:23 by rbetz             #+#    #+#             */
/*   Updated: 2022/12/02 11:27:13 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

// static void	execute_child(int *fds, t_cmd *cmd, t_env *env)
// {
// 	static int index_fd = 0;
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
// 	execve(cmd->argv[0], cmd->argv, create_envp_from_env(env));
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
	pid_t	pid;
	int		ret;
	// int		fds[2];

	// pipe(fds);
	pid = fork();
	if (pid == 0)
		// execute_child(fds, cmd, env)
		execve(cmd->argv[0], cmd->argv, create_envp_from_env(env));
	// close(fds[0]);
	// close(fds[1]);
	if (pid < 0)
		ft_error("minishell: exec_cmd:");
	waitpid(-1, &ret, 0);
	if (ret < 0)
		ft_error(cmd->argv[0]);
}

int	exec_builtin(t_cmd *cmd, t_data *data)
{
	if (cmd->argv[0][0] == 'c')
		cd(arraycount(cmd->argv), cmd->argv, data);
	else if (cmd->argv[0][0] == 'p')
		pwd(arraycount(cmd->argv), cmd->argv);
	// else if (cmd->argv[0][0] == 'u')
	// 	unset(arraycount(cmd->argv), cmd->argv, env);
	else if (ft_strcmp(cmd->name, "echo") == 0)
		echo(arraycount(cmd->argv), cmd->argv);
	else if (ft_strcmp(cmd->name, "env") == 0)
		print_env(data->env, 1);
	else if (ft_strcmp(cmd->name, "exit") == 0)
		return (shell_exit(cmd->argv));
	// else if (ft_strcmp(cmd->name, "export") == 0)
	// 	export(arraycount(cmd->argv), cmd->argv, env);
	return (-1);
}

/*If exit is found, exit status is returned. Otherwise return value is -1.*/
int	execute_list(t_cmd *lst, t_data *data)
{
	t_cmd	*current;
	int		ret;

	current = lst;
	ret = -1;
	if (lst == NULL)
		return (ret);
	//commands are executed one after another; needs to be changed to pipe
	while (current != NULL)
	{
		open_redir(lst, data->env);
		if (current->type == 0)
		{
			if (lst->argv[0][0] == 'c')
				cd(arraycount(lst->argv),lst->argv, data);
			else if (lst->argv[0][0] == 'p')
				pwd(arraycount(lst->argv), lst->argv);
			else if (lst->argv[0][0] == 'u')
				data->env = unset(arraycount(lst->argv), lst->argv, data->env);
			else if (ft_strcmp(lst->argv[0], "echo") == 0)
				echo(arraycount(lst->argv), lst->argv);
			else if (ft_strcmp(lst->argv[0], "export") == 0)
				data->env = export(arraycount(lst->argv), lst->argv, data->env);
			else if (ft_strcmp(lst->argv[0], "env") == 0)
				print_env(data->env, 1);
			else if (ft_strcmp(lst->argv[0], "exit") == 0)
				return (shell_exit(lst->argv));
			// else if (strcmp(lst->argv[0], "export") == 0)
				// export(arraycount(lst->argv), lst->argv, env);
		}
		if (current->type == 1)
			exec_cmd(current, data->env);
		// close_redir(lst);
		current = current->pipe;
	}
	return (ret);
}
