/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 10:32:37 by rbetz             #+#    #+#             */
/*   Updated: 2022/12/02 16:09:59 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirects.h"

static char	*get_file_path(char *file, t_env *env)
{
	if (ft_strchr(file, '/') == 0)
		file = combine_pathprog(get_env_var(env, "PWD"), file);
	else
		file = ft_strdup(file);
	if (file == NULL)
		return (NULL);
	else
		return (file);
}
void	file_input(t_cmd *cmd, t_env *env)
{
	int	i;

	i = 3;
	cmd->redir->file = get_file_path(cmd->redir->file, env);
	// printf("New_File:\t|%s|\n", cmd->file);
	if (access(cmd->redir->file, F_OK) < 0)
	{
		cmd->redir->file = ft_free(cmd->redir->file);
		ft_error("File does not exist");
	}
	if (access(cmd->redir->file, R_OK) < 0)
	{
		cmd->redir->file = ft_free(cmd->redir->file);
		ft_error("Can't read file. Permission denied.");
	}
	while (i < 10)
	{
		if (cmd->fds[i] == -1)
			break ;
		else
			i++;
	}
	if (i == 10)
		ft_error("Bad Filedescriptor");
	cmd->fds[i] = open(cmd->redir->file, O_RDONLY);
	// printf("fd for file:\t|%d|%s|\n", cmd->fds[2], cmd->file);
	cmd->redir->file = ft_free(cmd->redir->file);
}

static void	here_doc(t_cmd *cmd, t_env *env)
{
	(void)cmd;
	(void)env;
}

void	open_redir(t_cmd *cmd, t_env *env)
{
	t_redir	*tmp;
	
	tmp = cmd->redir;
	while (tmp != NULL)
	{
		// printf("Redir Address:\t|%p|\n", tmp);
		// printf("Original_File:\t|%s|\n", tmp->file);
		if (tmp->r_type == 1)
			file_input(cmd, env);
		else if (tmp->r_type == 3)
			here_doc(cmd, env);
		
		tmp = tmp->next;
	}
}

void	close_redir(t_cmd *cmd)
{
	int	i;

	i = 3;
	while (i < 10 && cmd->fds[i] != -1)
	{
		if (close(cmd->fds[i++]) < 0)
			ft_error("Bad filedescriptor");
	}
}
