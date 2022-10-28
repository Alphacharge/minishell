/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 13:14:35 by rbetz             #+#    #+#             */
/*   Updated: 2022/10/28 14:27:23 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <unistd.h>

typedef struct s_var
{
	int		calls;
	char	**path;
	char	*pwd;
	int		fd_in;
	int		fd_out;
	char	***args;
	char	*exec;
	int		scs;
	int		fds[FD_SETSIZE][2];
	int		index_fd;
	int		here;
	int		here_fd[2];
}			t_var;

#endif