/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 09:27:23 by rbetz             #+#    #+#             */
/*   Updated: 2022/12/22 09:58:23 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void close_and_neg(int *fd)
{
	if (VERBOSE == 1)
		printf("closing file descriptor %i\n", *fd);
	close(*fd);
	*fd = FD_UNUSED;
}

static int exec_bltin(t_cmd *cmd, t_prompt *prompt)
{
	if (cmd->argv[0][0] == 'c')
		cd(cmd->argv, cmd->env, prompt);
	else if (cmd->argv[0][0] == 'p')
		pwd(cmd->argv);
	else if (cmd->argv[0][0] == 'u')
		cmd->env = unset(cmd->argv, cmd->env);
	else if (ft_strcmp(cmd->argv[0], "echo") == 0)
		echo(cmd->argv);
	else if (ft_strcmp(cmd->argv[0], "export") == 0)
		cmd->env = export(arraycount(cmd->argv), cmd->argv, cmd->env);
	else if (ft_strcmp(cmd->argv[0], "env") == 0)
		env(cmd->argv, cmd->env);
	return (EXIT_SUCCESS);
}

static int exec_child(t_cmd *cmd, t_prompt *prompt)
{
	unset_signals();
	if (cmd->rats[WRITE] == FD_UNUSED && cmd->prev == NULL && cmd->next != NULL)
	{
		// ft_putendl_fd("-->1", 2);
		if (dup2(cmd->fds[WRITE], STDOUT) < 0)
			ft_error(NULL, NULL, "Error dup first cmd");
		close_and_neg(&cmd->fds[WRITE]);
	}
	else if (cmd->rats[READ] == FD_UNUSED && cmd->next == NULL && cmd->prev != NULL)
	{
		// ft_putendl_fd("-->2", 2);
		if (dup2(cmd->prev->fds[READ], STDIN) < 0)
			ft_error(NULL, NULL, "Error dup last cmd");
		close_and_neg(&cmd->prev->fds[READ]);
	}
	else if (cmd->rats[WRITE] == FD_UNUSED && cmd->rats[READ] == FD_UNUSED && cmd->next != NULL && cmd->prev != NULL)
	{
		// ft_putendl_fd("-->3", 2);
		if (dup2(cmd->fds[WRITE], STDOUT) < 0 || dup2(cmd->prev->fds[READ], STDIN) < 0)
			ft_error(NULL, NULL, "Error dup mid cmd");
		close_and_neg(&cmd->prev->fds[READ]);
		close_and_neg(&cmd->fds[WRITE]);
	}
	if (cmd->rats[READ] != FD_UNUSED)
	{
		// ft_putendl_fd("-->4", 2);
		if (dup2(cmd->rats[READ], STDIN) < 0)
			ft_error(NULL, NULL, "Error dup file in cmd");
		close_and_neg(&cmd->rats[READ]);
	}
	if (cmd->rats[WRITE] != FD_UNUSED)
	{
		// ft_putendl_fd("-->5", 2);
		if (dup2(cmd->rats[WRITE], STDOUT) < 0)
			ft_error(NULL, NULL, "Error dup file out cmd");
		close_and_neg(&cmd->rats[WRITE]);
	}
	if (cmd->type == BLTIN)
	{
		exit(exec_bltin(cmd, prompt));
	}
	else if (execve(cmd->argv[0], cmd->argv, create_envp_from_env(cmd->env)) != 0)
		exit(EXIT_FAILURE);
	return (0);
}

static void close_pipe_fds(t_cmd *cmd)
{
	// first command, close only writeend of pipe
	if (cmd->prev == NULL && cmd->next != NULL)
		close_and_neg(&cmd->fds[WRITE]);
	// last command, close only readend of prev pipe
	else if (cmd->next == NULL && cmd->prev != NULL)
		close_and_neg(&cmd->prev->fds[READ]);
	// middle command, close readend of prev pipe and writeend of pipe
	else if (cmd->next != NULL && cmd->prev != NULL)
	{
		close_and_neg(&cmd->prev->fds[READ]);
		close_and_neg(&cmd->fds[WRITE]);
	}
}
static void close_reds_fds(t_cmd *cmd)
{
	if (cmd->rats[READ] != FD_UNUSED)
		close_and_neg(&cmd->rats[READ]);
	if (cmd->rats[WRITE] != FD_UNUSED)
		close_and_neg(&cmd->rats[WRITE]);
}

static void exec_cmd(t_cmd *cmd, t_prompt *prompt)
{
	pid_t pid;

	if (cmd->next != NULL)
		pipe(cmd->fds);
	pid = fork();
	if (pid == 0)
	{
			exec_child(cmd, prompt);
	}
	close_pipe_fds(cmd);
	close_reds_fds(cmd);
	if (pid < 0)
		ft_error(NULL, "fork", NULL);
}



/*If exit is found, exit status is returned. Otherwise return value is -1.*/
int execute_list(t_cmd *lst, t_prompt *prompt)
{
	t_cmd 		*cmd;
	static int	ret = 0;

	cmd = lst;
	if (cmd == NULL)
		return (-1);
	cmd = create_redirs(cmd);
	while (cmd != NULL)
	{
		if (ft_strcmp(cmd->argv[0], "exit") == 0)
			return (shell_exit(cmd->argv));
		exec_cmd(cmd, prompt);
		cmd = cmd->next;
	}
	while ((waitpid(-1, &ret, WNOHANG)) != -1)
	{
		if (WIFEXITED(ret) == true)
			ret = WEXITSTATUS(ret);
	}
	return (-1);
}
