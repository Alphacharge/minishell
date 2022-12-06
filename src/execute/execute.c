/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 09:27:23 by rbetz             #+#    #+#             */
/*   Updated: 2022/12/06 20:09:50 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static void close_and_neg(int *fd)
{
	close(*fd);
	*fd = INT32_MIN;
}

static void close_filedescriptors(t_cmd *cmd)
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
static void execute_child(t_cmd *cmd, t_env *env)
{
	// printf("-->10<--\n");
	if (cmd->prev == NULL && cmd->next != NULL)
	{
	// first cmd
	// printf("-->9<--\n");
		// printf(">%d\n", cmd->fds[1]);
		if (dup2(cmd->fds[1], 1) < 0)
			ft_error("Error dup first cmd");
		close_and_neg(&cmd->fds[1]);
		// printf(">>%d\n", cmd->fds[1]);
	// printf("-->4<--\n");
	}
	else if (cmd->next == NULL && cmd->prev != NULL)
	{
	// printf("-->8<--\n");
		// last cmd
		if (dup2(cmd->prev->fds[0], 0) < 0)
			ft_error("Error dup last cmd");
		close_and_neg(&cmd->prev->fds[0]);
	// printf("-->5<--\n");
	}
	else if (cmd->next != NULL && cmd->prev != NULL)
	{
	// printf("-->11<--\n");
		// other cmd
		if (dup2(cmd->fds[1], 1) < 0 || dup2(cmd->prev->fds[0], 0) < 0)
			ft_error("Error dup mid cmd");
		close_and_neg(&cmd->prev->fds[0]);
		close_and_neg(&cmd->fds[1]);
	// printf("-->12<--\n");
	}
	// close_and_neg(&cmd->fds[0]);
	// close_and_neg(&cmd->fds[1]);
	close_filedescriptors(cmd);
	// printf("-->1<--:%s\n", cmd->argv[0]);
	execve(cmd->argv[0], cmd->argv, create_envp_from_env(env));
}

static void exec_cmd(t_cmd *cmd, t_env *env)
{
	pid_t pid;
	int ret;
	static int index_fd = 0;

	// index_fd = 0;
	// printf("-->2<--%d\n", index_fd);
	if (cmd->next != NULL)
		pipe(cmd->fds);
	ret = 0;
	pid = fork();
	if (pid == 0)
	{
	// printf("-->3<--\n");
		execute_child(cmd, env);
		exit(0);
		// execve(cmd->argv[0], cmd->argv, create_envp_from_env(env));
	}
	if (pid < 0)
		ft_error(NULL);
	if (ret < 0)
		ft_error(cmd->argv[0]);
	if (cmd->prev == NULL && cmd->next != NULL)
		close_and_neg(&cmd->fds[1]);
	else if (cmd->next == NULL && cmd->prev != NULL)
		close_and_neg(&cmd->prev->fds[0]);
	else if (cmd->next != NULL && cmd->prev != NULL)
	{
		close_and_neg(&cmd->prev->fds[0]);
		close_and_neg(&cmd->fds[1]);
	}
	// else
	// {
	// 	close_and_neg(&cmd->fds[0]);
	// 	close_and_neg(&cmd->fds[1]);
	// }
	// waitpid(pid, &ret, 0);
	// while ((waitpid(-1, &ret, WNOHANG)) > 0)
	// 	;
		// printf("child %d terminated\n", pid);
	index_fd++;
	// close_filedescriptors(cmd);
}

/*If exit is found, exit status is returned. Otherwise return value is -1.*/
int execute_list(t_cmd *lst, t_prompt *prompt, int std_out)
{
	t_cmd *current;

	current = lst;
	if (lst == NULL)
		return (-1);
	// commands are executed one after another; needs to be changed to pipe
	while (current != NULL)
	{
		// added redirection validity check
		// if (open_redir(lst, lst->env) == 1)
		// 	return (-1);
		if (current->type == BLTIN)
		{
			if (lst->argv[0][0] == 'c')
				cd(arraycount(lst->argv), lst->argv, lst->env, prompt);
			else if (lst->argv[0][0] == 'p')
				pwd(arraycount(lst->argv), lst->argv);
			else if (lst->argv[0][0] == 'u')
				lst->env = unset(arraycount(lst->argv), lst->argv, lst->env);
			else if (ft_strcmp(lst->argv[0], "echo") == 0)
				echo(arraycount(lst->argv), lst->argv);
			else if (ft_strcmp(lst->argv[0], "export") == 0)
				lst->env = export(arraycount(lst->argv), lst->argv, lst->env);
			else if (ft_strcmp(lst->argv[0], "env") == 0)
				print_env(lst->env, 1);
			else if (ft_strcmp(lst->argv[0], "exit") == 0)
				return (shell_exit(lst->argv));
		}
		if (current->type == EXEC)
			exec_cmd(current, lst->env);
		// if (close_redir(lst) == 1)
		// 	return (-1);
		current = current->next;
	}
	int ret = 0;
	while ((waitpid(-1, &ret, WNOHANG)) != -1)
		;
	// Max sagte ds ist wichtig
	(void)std_out;
	// if (dup2(std_out, 0) < 0)
	// 		ft_error("Error dup stdout");
	
	return (-1);
}
