/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 10:32:37 by rbetz             #+#    #+#             */
/*   Updated: 2022/12/02 11:40:01 by rbetz            ###   ########.fr       */
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

void	open_redir(t_cmd *cmd, t_env *env)
{
	t_redir	*tmp;
	
	tmp = cmd->redir;
	while (tmp != NULL)
	{
		printf("Redir Address:\t|%p|\n", tmp);
		printf("Original_File:\t|%s|\n", tmp->file);
		tmp->file = get_file_path(tmp->file, env);
		printf("New_File:\t|%s|\n", tmp->file);
		if (access(tmp->file, F_OK) < 0)
		{
			tmp->file = ft_free(tmp->file);
			ft_error("File does not exist");
		}
		if (access(tmp->file, R_OK) < 0)
		{
			tmp->file = ft_free(tmp->file);
			ft_error("Can't read file. Permission denied.");
		}
		cmd->fds[2] = open(tmp->file, O_RDONLY);
		printf("fd for file:\t|%d|%s|\n", cmd->fds[2], tmp->file);
		tmp->file = ft_free(tmp->file);
		tmp = tmp->next;
	}
}

// void	close_redir(t_cmd *cmd)
// {
	
// }
