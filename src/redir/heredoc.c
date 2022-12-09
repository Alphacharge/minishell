/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 10:03:58 by rbetz             #+#    #+#             */
/*   Updated: 2022/12/09 10:45:46 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirects.h"
#include "execute.h"

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
		write(cmd->rats[1], new, len);
		if (ft_strcmp(new, limiter) == 0)
		{
			free(new);
			break ;
		}
		free(new);
	}
	free(limiter);
	close(cmd->rats[1]);
}

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
			if (tred->r_type == HERE)
			{
				if (tmp->rats[0] != INT32_MIN)
					close_both_fds(tmp);
				get_here(tmp, tred->file);
				tmp->here = true;
			}
			tred = tred->next;
		}
		tmp = tmp->next;
	}
	return (cmd);
}
