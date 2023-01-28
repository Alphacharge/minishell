/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humbi <humbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 12:00:43 by rbetz             #+#    #+#             */
/*   Updated: 2023/01/28 14:53:24 by humbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_hist	init_history(void)
{
	t_hist	hist;
	char	*line;

	hist.fd = open(FILENAME, O_RDWR | O_APPEND | O_CREAT, 0644);
	if (hist.fd == -1 && !access(FILENAME, F_OK))
		hist.fd = open(ALTFILENAME, O_RDWR | O_APPEND | O_CREAT, 0644);
	line = get_next_line(hist.fd);
	while (line != NULL)
	{
		ft_strreplace(line, "\n", "\0");
		add_history(line);
		free(line);
		line = get_next_line(hist.fd);
	}
	return (hist);
}
