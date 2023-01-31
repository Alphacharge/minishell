/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 10:03:58 by rbetz             #+#    #+#             */
/*   Updated: 2023/01/31 18:58:38 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*reading heredoc in a pipe*/
static void	get_here(t_cmd *cmd, char *lim, t_data *data)
{
	char	*limiter;
	char	*tmp;
	char	*new;
	int		len;

	limiter = ft_strjoin(lim, "\n");
	pipe(cmd->reds);
	while (1)
	{
		write(2, ">", 1);
		tmp = get_next_line(0);
		new = expand_envvars(tmp, data);
		free(tmp);
		len = ft_strlen(new);
		if (ft_strcmp(new, limiter) == 0)
		{
			free(new);
			break ;
		}
		else
			write(cmd->reds[WRITE], new, len);
		free(new);
	}
	free(limiter);
	close_and_neg(&cmd->reds[WRITE]);
}

/*Check redirs for heredocs, ask 4 all but store only the last*/
t_cmd	*handle_heredocs(t_cmd *cmd, t_data *data)
{
	t_cmd	*tmp;
	t_redir	*tred;

	tmp = cmd;
	while (tmp != NULL)
	{
		tred = tmp->redir;
		while (tred != NULL)
		{
			if (tred->type == HERE)
			{
				if (tmp->reds[READ] != FD_UNUSED)
					close_reds_fds(tmp);
				get_here(tmp, tred->file, data);
				tmp->here = true;
			}
			tred = tred->next;
		}
		tmp = tmp->next;
	}
	return (cmd);
}
