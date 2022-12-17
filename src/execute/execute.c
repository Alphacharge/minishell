/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humbi <humbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 09:27:23 by rbetz             #+#    #+#             */
/*   Updated: 2022/12/17 14:31:16 by humbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	close_and_neg(int *fd)
{
	close(*fd);
	*fd = FD_UNUSED;
}

static void	execute_child(t_cmd *cmd, t_env *env)
{
	if (cmd->rats[WRITE] == FD_UNUSED && cmd->prev == NULL && cmd->next != NULL)
	{
// ft_putendl_fd("-->1", 2);
		if (dup2(cmd->fds[WRITE], STDOUT) < 0)
			ft_error("Error dup first cmd");
		close_and_neg(&cmd->fds[WRITE]);
	}
	else if (cmd->rats[READ] == FD_UNUSED && cmd->next == NULL && cmd->prev != NULL)
	{
// ft_putendl_fd("-->2", 2);
		if (dup2(cmd->prev->fds[READ], STDIN) < 0)
			ft_error("Error dup last cmd");
		close_and_neg(&cmd->prev->fds[READ]);
	}
	else if (cmd->rats[WRITE] == FD_UNUSED && cmd->rats[READ] == FD_UNUSED && cmd->next != NULL && cmd->prev != NULL)
	{
// ft_putendl_fd("-->3", 2);
		if (dup2(cmd->fds[WRITE], STDOUT) < 0 || dup2(cmd->prev->fds[READ], STDIN) < 0)
			ft_error("Error dup mid cmd");
		close_and_neg(&cmd->prev->fds[READ]);
		close_and_neg(&cmd->fds[WRITE]);
	}
	if (cmd->rats[READ] != FD_UNUSED)
	{
// ft_putendl_fd("-->4", 2);
		if (dup2(cmd->rats[READ], STDIN) < 0)
			ft_error("Error dup file in cmd");
		close_and_neg(&cmd->rats[READ]);
	}
	if (cmd->rats[WRITE] != FD_UNUSED)
	{
// ft_putendl_fd("-->5", 2);
		if (dup2(cmd->rats[WRITE], STDOUT) < 0)
			ft_error("Error dup file out cmd");
		close_and_neg(&cmd->rats[WRITE]);
	}
	execve(cmd->argv[0], cmd->argv, create_envp_from_env(env));
}
static void	close_pipe_fds(t_cmd *cmd)
{
	//first command, close only writeend of pipe
	if (cmd->prev == NULL && cmd->next != NULL)
		close_and_neg(&cmd->fds[WRITE]);
	//last command, close only readend of prev pipe
	else if (cmd->next == NULL && cmd->prev != NULL)
		close_and_neg(&cmd->prev->fds[READ]);
	//middle command, close readend of prev pipe and writeend of pipe
	else if (cmd->next != NULL && cmd->prev != NULL)
	{
		close_and_neg(&cmd->prev->fds[READ]);
		close_and_neg(&cmd->fds[WRITE]);
	}
}
static void	exec_cmd(t_cmd *cmd, t_env *env)
{
	pid_t		pid;
	static int	index_fd = 0;

	if (cmd->next != NULL)
		pipe(cmd->fds);
	pid = fork();
	if (pid == 0)
	{
		execute_child(cmd, env);
		exit(0);
	}
	if (pid < 0)
		ft_error(NULL);
	close_pipe_fds(cmd);
	// heredoc or infile 4 current command
	if (cmd->rats[READ] != FD_UNUSED)
		close_and_neg(&cmd->rats[READ]);
	if (cmd->rats[WRITE] != FD_UNUSED)
		close_and_neg(&cmd->rats[WRITE]);
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
		if (cmd->type == EXEC && cmd->error == false)
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
