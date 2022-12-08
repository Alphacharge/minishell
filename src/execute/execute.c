/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 09:27:23 by rbetz             #+#    #+#             */
/*   Updated: 2022/12/08 17:08:06 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	close_and_neg(int *fd)
{
	close(*fd);
	*fd = INT32_MIN;
}

static void	close_filedescriptors(t_cmd *cmd)
{
	while (cmd != NULL)
	{
		if (cmd->fds[0] != INT32_MIN)
			close_and_neg(&cmd->fds[0]);
		if (cmd->fds[1] != INT32_MIN)
			close_and_neg(&cmd->fds[1]);
		cmd = cmd->prev;
	}
}

static void	execute_child(t_cmd *cmd, t_env *env)
{
	if (cmd->fds[1] != INT32_MIN && cmd->prev == NULL && cmd->next != NULL)
	{
		if (dup2(cmd->fds[1], 1) < 0)
			ft_error("Error dup first cmd");
		close_and_neg(&cmd->fds[1]);
	}
	else if (cmd->next == NULL && cmd->prev != NULL)
	{
		if (dup2(cmd->prev->fds[0], 0) < 0)
			ft_error("Error dup last cmd");
		close_and_neg(&cmd->prev->fds[0]);
	}
	else if (cmd->next != NULL && cmd->prev != NULL)
	{
		if (dup2(cmd->fds[1], 1) < 0 || dup2(cmd->prev->fds[0], 0) < 0)
			ft_error("Error dup mid cmd");
		close_and_neg(&cmd->prev->fds[0]);
		close_and_neg(&cmd->fds[1]);
	}
	if (cmd->rats[0] != INT32_MIN)
	{
		if (dup2(cmd->rats[0], 0) < 0)
			ft_error("Error dup here cmd");
		close_and_neg(&cmd->rats[0]);
	}
	close_filedescriptors(cmd);
	execve(cmd->argv[0], cmd->argv, create_envp_from_env(env));
}

static void	exec_cmd(t_cmd *cmd, t_env *env)
{
	pid_t		pid;
	static int	index_fd = 0;

	// ft_putnbr_fd(cmd->fds[0], 2);
	if (cmd->next != NULL)
		pipe(cmd->fds);
	// ft_putnbr_fd(cmd->fds[0], 2);
	// ft_putnbr_fd(cmd->fds[1], 2);
	pid = fork();
	if (pid == 0)
	{
		execute_child(cmd, env);
		exit(0);
	}
	if (pid < 0)
		ft_error(NULL);
	if (cmd->prev == NULL && cmd->next != NULL)
		close_and_neg(&cmd->fds[1]);
	else if (cmd->next == NULL && cmd->prev != NULL)
		close_and_neg(&cmd->prev->fds[0]);
	else if (cmd->next != NULL && cmd->prev != NULL)
	{
		close_and_neg(&cmd->prev->fds[0]);
		close_and_neg(&cmd->fds[1]);
	}
	if (cmd->rats[0] != INT32_MIN)
		close_and_neg(&cmd->rats[0]);
	index_fd++;
}

/*If exit is found, exit status is returned. Otherwise return value is -1.*/
int	execute_list(t_cmd *lst, t_prompt *prompt)
{
	t_cmd	*cmd;
	int		ret;

	cmd = lst;
	ret = 0;
	if (cmd == NULL)
		return (-1);
	cmd = create_redirs(cmd);
	while (cmd != NULL)
	{
		if (cmd->type == BLTIN)
		{
			if (cmd->argv[0][0] == 'c')
				cd(arraycount(cmd->argv), cmd->argv, cmd->env, prompt);
			else if (cmd->argv[0][0] == 'p')
				pwd(arraycount(cmd->argv), cmd->argv);
			else if (cmd->argv[0][0] == 'u')
				cmd->env = unset(arraycount(cmd->argv), cmd->argv, cmd->env);
			else if (ft_strcmp(cmd->argv[0], "echo") == 0)
				echo(arraycount(cmd->argv), cmd->argv);
			else if (ft_strcmp(cmd->argv[0], "export") == 0)
				cmd->env = export(arraycount(cmd->argv), cmd->argv, cmd->env);
			else if (ft_strcmp(cmd->argv[0], "env") == 0)
				print_env(cmd->env, 1);
			else if (ft_strcmp(cmd->argv[0], "exit") == 0)
				return (shell_exit(cmd->argv));
		}
		if (cmd->type == EXEC)
			exec_cmd(cmd, cmd->env);
		cmd = cmd->next;
	}
	while ((waitpid(-1, &ret, WNOHANG)) != -1)
	{
		if (WIFEXITED(ret) == true)
		ret = WEXITSTATUS(ret);
	}
	return (-1);
}
