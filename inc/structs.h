/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 13:14:35 by rbetz             #+#    #+#             */
/*   Updated: 2022/12/06 19:45:41 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# define INPUT		1
# define OUTPUT		2
# define HERE		3
# define APPEND		4

# define BLTIN		0
# define EXEC		1
# define REDIR		2
# define PIPE		3
# define LIST		4
# define BACK		5

# include <unistd.h>
# include <sys/types.h>
# include "environment.h"
# include "history.h"

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
	char			*file;
	int				r_type;
	// char	*efile;
	// char	*mode;
	// int		fd;
	// char	*cmd;
	struct s_redir	*next;
}				t_redir;

typedef struct s_param
{
	char			*arg;
	struct s_param	*next;
}					t_param;

typedef struct s_cmd
{
	int				type;
	char			*name;
	char			**argv;
	int				fds[2];
	struct s_env	*env;
	struct s_cmd	*next;
	struct s_cmd	*prev;
	struct s_redir	*redir;
	struct s_param	*param;
}					t_cmd;

typedef struct s_data
{
	char			*input;
	int				std_out;
	struct s_prompt	*prompt;
	struct s_hist	hist;
	struct s_env	*env;
}					t_data;
#endif
