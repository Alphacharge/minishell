/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humbi <humbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 10:03:58 by rbetz             #+#    #+#             */
/*   Updated: 2022/12/19 14:12:10 by humbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirects.h"
#include "execute.h"

/*reading heredoc in a pipe*/
static void	get_here(t_cmd *cmd, char *lim)
{
	char	*limiter;
	char	*tmp;
	char	*new;
	int		len;

	limiter = ft_strjoin(lim, "\n");
	pipe(cmd->rats);
	while (1)
	{
		write(2, ">", 1);
		tmp = get_next_line(0);
		new = expand_envvars(tmp, cmd->env);
		free(tmp);
		len = ft_strlen(new);
		if (ft_strcmp(new, limiter) == 0)
		{
			free(new);
			break ;
		}
		else
			write(cmd->rats[WRITE], new, len);
		free(new);
	}
	free(limiter);
	close(cmd->rats[WRITE]);
}

/*Check redirs for heredocs, ask 4 all but store only the last*/
t_cmd	*handle_heredocs(t_cmd *cmd)
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
				if (tmp->rats[READ] != FD_UNUSED)
					close_both_rats(tmp);
				get_here(tmp, tred->file);
				tmp->here = true;
			}
			tred = tred->next;
		}
		tmp = tmp->next;
	}
	return (cmd);
}
