/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 13:14:35 by rbetz             #+#    #+#             */
/*   Updated: 2022/11/25 15:29:12 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <unistd.h>
# include <sys/types.h>
# include "environment.h"

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

typedef struct s_prompt
{
	char	*name;
	char	*dir;
	char	*seperator;
	char	*endl;
	char	*prompt;
}				t_prompt;

typedef struct s_pipe
{
	int	type;
	int	left;
	int	right;
}				t_pipe;

typedef struct s_exec
{
	char	**argv;
	char	**eargv;
}				t_exec;

typedef struct s_redir
{
	char	*file;
	// char	*efile;
	// char	*mode;
	// int		fd;
	// char	*cmd;
	struct s_redir	*next;
}				t_redir;

typedef struct s_cmd
{
	int				type;
	char			**argv;
	struct s_env	*env;
	struct s_cmd	*pipe;
	struct s_redir	*redir;
}					t_cmd;

typedef struct s_data
{
	char		*input;
	t_prompt	prompt;
}				t_data;
#endif
