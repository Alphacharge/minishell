/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 09:27:23 by rbetz             #+#    #+#             */
/*   Updated: 2023/02/14 09:12:42 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	reset_fds(t_cmd *cmd)
{
	close_reds_fds(cmd);
	if (dup2(cmd->stdinsaver, STDIN) < 0)
		ft_error(NULL, NULL, 9);
	close(cmd->stdinsaver);
	if (dup2(cmd->stdoutsaver, STDOUT) < 0)
		ft_error(NULL, NULL, 9);
	close(cmd->stdoutsaver);
}

/*Executes builtin and resets fd.*/
static int	exec_bltin(t_cmd *cmd, t_prompt *prompt)
{
	int	ret;

	ret = 0;
	cmd->stdinsaver = dup(STDIN);
	cmd->stdoutsaver = dup(STDOUT);
	dup_reds_fds(cmd);
	if (cmd->argv[0][0] == 'c')
		ret = cd(cmd->argv, cmd->data->env, prompt);
	else if (cmd->argv[0][0] == 'p')
		ret = pwd();
	else if (cmd->argv[0][0] == 'u')
		ret = unset(cmd->argv, cmd->data);
	else if (ft_strcmp(cmd->argv[0], "echo") == 0)
		ret = echo(cmd->argv);
	else if (ft_strcmp(cmd->argv[0], "export") == 0)
		ret = export(arraycount(cmd->argv), cmd->argv, cmd->data);
	else if (ft_strcmp(cmd->argv[0], "env") == 0)
		ret = env(cmd->argv, cmd->data->env);
	reset_fds(cmd);
	return (ret);
}

/*Child process routine. Runs execve or builtin.*/
static void	exec_child(t_cmd *cmd, t_prompt *prompt)
{
	char	**envp;

	unset_signals();
	dup_pipe_fds(cmd);
	dup_reds_fds(cmd);
	close_pipe_fds(cmd);
	if (cmd->type == BLTIN)
		exit(exec_bltin(cmd, prompt));
	envp = create_envp_from_env(cmd->data->env);
	if (cmd->error == false)
		execve(cmd->argv[0], cmd->argv, envp);
	free_ptr_array((void **) envp);
	exit(EXIT_FAILURE);
}

/*Executes one cmd node. Only forks builtins if needed.*/
static int	exec_cmd(t_cmd *cmd, t_prompt *prompt)
{
	pid_t	pid;

	pid = INT32_MAX;
	if (cmd->prev == NULL && cmd->next == NULL && cmd->type == BLTIN)
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
		return (ft_error("fork", NULL, 1));
	return (0);
}

/*If exit is found, exit status is returned. Otherwise return value is -1.*/
int	execute_list(t_cmd *lst, t_data *data)
{
	t_cmd	*cmd;

	cmd = lst;
	if (cmd == NULL)
		return (-1);
	cmd = create_redirs(cmd, data);
	while (cmd != NULL)
	{
		if (ft_strcmp(cmd->argv[0], "exit") == 0)
			return (shell_exit(cmd->argv));
		data->exitstatus = exec_cmd(cmd, data->prompt);
		cmd = cmd->next;
	}
	while ((waitpid(-1, &data->exitstatus, WNOHANG)) != -1)
	{
		if (WIFEXITED(data->exitstatus) == true)
			data->exitstatus = WEXITSTATUS(data->exitstatus);
	}
	return (-1);
}
