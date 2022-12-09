/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 10:32:37 by rbetz             #+#    #+#             */
/*   Updated: 2022/12/09 10:19:09 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirects.h"
#include "execute.h"

// static char	*get_file_path(char *file, t_env *env)
// {
// 	if (ft_strchr(file, '/') == 0)
// 		file = combine_pathprog(get_env_var(env, "PWD"), file);
// 	else
// 		file = ft_strdup(file);
// 	if (file == NULL)
// 		return (NULL);
// 	else
// 		return (file);
// }

// changed function to take redir node as parameter;
// otherwise it will always parse the first redir node of cmd
//  static int	file_input(t_cmd *cmd, t_redir *redir)
//  {
//  	int	i;

// 	i = 3;
// 	redir->file = get_file_path(redir->file, cmd->env);
// 	// printf("New_File:\t|%s|\n", redir->file);
// //added error handling
// 	if (access(redir->file, F_OK) < 0 || access(redir->file, R_OK) < 0)
// 		return (ft_error(redir->file),
// 			redir->file = ft_free(redir->file), 1);
// 	while (i < 10)
// 	{
// 		if (cmd->fds[i] == -1)
// 			break ;
// 		else
// 			i++;
// 	}
// 	if (i == 10)
// 		return (ft_error(redir->file), 1);
// 	cmd->fds[i] = open(redir->file, O_RDONLY);
// 	// printf("fd for file:\t|%d|%s|\n", cmd->fds[2], redir->file);
// 	redir->file = ft_free(redir->file);
// 	return (0);
// }

// static int	here_doc(t_cmd *cmd, t_env *env)
// {
// 	(void)cmd;
// 	(void)env;
// 	return (0);
// }

/*Opens every redirection node of cmd.*/
// int	open_redir(t_cmd *cmd, t_env *env)
// {
// 	t_redir	*tmp;

// 	tmp = cmd->redir;
// 	while (tmp != NULL)
// 	{
// 		// printf("Redir Address:\t|%p|\n", tmp);
// 		// printf("Original_File:\t|%s|\n", tmp->file);
// //added error handling
// 		if (tmp->r_type == INPUT && file_input(cmd, tmp) == 1)
// 			return (1);
// 		if (tmp->r_type == HERE && here_doc(cmd, env) == 1)
// 			return (1);
// 		tmp = tmp->next;
// 	}
// 	return (0);
// }

// added error handling, not sure if needed
//  int	close_redir(t_cmd *cmd)
//  {
//  	int	i;

// 	i = 3;
// 	while (i < 10 && cmd->fds[i] != -1)
// 		if (close(cmd->fds[i++]) < 0)
// 			return (ft_error(NULL), 1);
// 	return (0);
// }
void	close_both_fds(t_cmd *cmd)
{
	if (cmd->fds[0] != INT32_MIN)
		close_and_neg(&cmd->fds[0]);
	if (cmd->fds[1] != INT32_MIN)
		close_and_neg(&cmd->fds[1]);
}

t_cmd	*create_redirs(t_cmd *cmd)
{
	cmd = handle_heredocs(cmd);
	cmd = handle_infiles(cmd);
	// cmd = handle_outfiles(cmd);
	return (cmd);
}

//------------------------
// void	check_outfile(t_var *var, int argc, char **argv)
// {
// 	char	*file;

// 	if (ft_strchr(argv[argc - 1], '/') == 0)
// 		file = combine_pathprog(var->pwd, argv[argc - 1]);
// 	else
// 		file = ft_strdup(argv[argc - 1]);
// 	if (!var->here)
// 		var->fd_out = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
// 	else
// 		var->fd_out = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
// 	free(file);
// 	if (var->fd_out < 0)
// 		ft_error(var, 4);
// }
