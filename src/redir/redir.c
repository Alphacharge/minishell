/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humbi <humbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 10:32:37 by rbetz             #+#    #+#             */
/*   Updated: 2022/12/15 11:33:32 by humbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirects.h"
#include "execute.h"

void	close_both_fds(t_cmd *cmd)
{
	if (cmd->fds[READ] != FD_UNUSED)
		close_and_neg(&cmd->fds[READ]);
	if (cmd->fds[WRITE] != FD_UNUSED)
		close_and_neg(&cmd->fds[WRITE]);
}
void	close_both_rats(t_cmd *cmd)
{
	if (cmd->rats[READ] != FD_UNUSED)
		close_and_neg(&cmd->rats[READ]);
	if (cmd->rats[WRITE] != FD_UNUSED)
		close_and_neg(&cmd->rats[WRITE]);
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
