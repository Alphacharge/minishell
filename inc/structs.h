/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 13:14:35 by rbetz             #+#    #+#             */
/*   Updated: 2023/02/07 20:27:19 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_prompt
{
	char	*name;
	char	*dir;
	char	*seperator;
	char	*endl;
	char	*prompt;
}				t_prompt;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_hist
{
	int				fd;
}					t_hist;

typedef struct s_exec
{
	char	**argv;
	char	**eargv;
}				t_exec;

typedef struct s_redir
{
	char			*file;
	int				type;
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
	int				reds[2];
	bool			error;
	bool			here;
	int				stdoutsaver;
	struct s_data	*data;
	struct s_cmd	*next;
	struct s_cmd	*prev;
	struct s_redir	*redir;
	struct s_param	*param;
}					t_cmd;

typedef struct s_data
{
	char			*input;
	struct s_prompt	*prompt;
	struct s_hist	hist;
	char			*exitstatus;
	struct s_env	*env;
	struct s_cmd	*cmd_head;
}					t_data;
#endif
