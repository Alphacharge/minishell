/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 09:27:23 by rbetz             #+#    #+#             */
/*   Updated: 2022/12/23 14:37:38 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static int	exec_bltin(t_cmd *cmd, t_prompt *prompt)
{
	if (cmd->argv[0][0] == 'c')
		return (cd(cmd->argv, cmd->data->env, prompt));
	else if (cmd->argv[0][0] == 'p')
		return (pwd(cmd->argv));
	else if (cmd->argv[0][0] == 'u')
		return (unset(cmd->argv, cmd->data));
	else if (ft_strcmp(cmd->argv[0], "echo") == 0)
		return (echo(cmd->argv));
	else if (ft_strcmp(cmd->argv[0], "export") == 0)
		return (export(arraycount(cmd->argv), cmd->argv, cmd->data));
	else if (ft_strcmp(cmd->argv[0], "env") == 0)
		return (env(cmd->argv, cmd->data->env));
	return (1);
}

static int	exec_child(t_cmd *cmd, t_prompt *prompt)
{
	unset_signals();
	dup_pipe_fds(cmd);
	dup_reds_fds(cmd);
	close_pipe_fds(cmd);
	if (cmd->type == BLTIN)
		exit(exec_bltin(cmd, prompt));
	else if (execve(cmd->argv[0], cmd->argv, create_envp_from_env(cmd->data->env)) != 0)
		exit(EXIT_FAILURE);
	return (0);
}

static int	exec_cmd(t_cmd *cmd, t_prompt *prompt)
{
	pid_t	pid;

	pid = INT32_MAX;
	if (cmd->next == NULL && cmd->type == BLTIN)
		return (exec_bltin(cmd, prompt));
	else
	{
		if (cmd->next != NULL)
			pipe(cmd->fds);
		pid = fork();
		if (pid == 0)
			exec_child(cmd, prompt);
	}
	close_piping(cmd);
	close_reds_fds(cmd);
	if (pid < 0)
		ft_error(NULL, "fork", NULL);
	return (0);
}

/*If exit is found, exit status is returned. Otherwise return value is -1.*/
int	execute_list(t_cmd *lst, t_data *data)
{
	t_cmd		*cmd;

	cmd = lst;
	if (cmd == NULL)
		return (data->exit_status = 1, -1);
	cmd = create_redirs(cmd, data);
	while (cmd != NULL)
	{
		if (ft_strcmp(cmd->argv[0], "exit") == 0)
			return (shell_exit(cmd->argv));
		data->exit_status = exec_cmd(cmd, data->prompt);
		cmd = cmd->next;
	}
	while ((waitpid(-1, &data->exit_status, WNOHANG)) != -1)
	{
		if (WIFEXITED(data->exit_status) == true)
			data->exit_status = WEXITSTATUS(data->exit_status);
	}
	return (-1);
}
