/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humbi <humbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:18:50 by rbetz             #+#    #+#             */
/*   Updated: 2023/01/28 15:43:23 by humbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h> // malloc, free, exit
# include <unistd.h> // close, read, write, dup2, access, fork, pipe, execve
# include <fcntl.h> // open
# include <sys/wait.h> // wait, waitpid
# include <stdio.h> // fprintf(int fd, char *stringset, ...) perror
# include <readline/history.h> //readline history
# include <readline/readline.h> //readline
# include <stdbool.h> //true false
//# include <dirent.h> //unbekannt von builtins
# include <sys/stat.h> //unbekannt von parsing
# include <sys/types.h> //unbekannt von structs

# include "libft.h"
# include "definitions.h"
# include "structs.h"

//Globals
int		g_exit_status;

//Builtins
int		cd(char **argv, t_env *env, t_prompt *prompt);
int		echo(char **argv);
int		env(char **argv, t_env *env);
int		shell_exit(char **argv);
int		export(int argc, char **argv, t_data *data);
void	export_print(t_env *env);
int		pwd(char **argv);
int		unset(char **argv, t_data *data);

//Environment
t_env	*extract_env(char **envp);
void	print_env(t_env *env, int fd);
void	delete_env(t_env *env);
char	**create_envp_from_env(t_env *env);
char	**get_path_var(t_env *env);
char	*get_path(char *executable, t_env *env);
char	*get_env_var(t_env *env, char *name);
t_env	*set_env_var(t_env *env, char *name, char *value);
t_env	*new_env(void);

//Errorhandling
int		ft_error(char *function, char *filename, int error);

//Executing
int		execute_list(t_cmd *lst, t_data *data);
void	dup_pipe_fds(t_cmd *cmd);
void	dup_reds_fds(t_cmd *cmd);
void	close_pipe_fds(t_cmd *cmd);
void	close_reds_fds(t_cmd *cmd);
void	close_piping(t_cmd *cmd);
void	close_and_neg(int *fd);

//History
t_hist	init_history(void);

//Memory
void	*free_cmds(t_cmd *cmd);
void	*free_cmds_error(t_cmd *cmd);
void	ms_cleanup(t_data *data);

//Parsing
t_cmd	*parse(char *s, t_data *data);
char	*expand_envvars(char *s, t_data *data);
t_cmd	*input_to_lst(char *s, t_data *data);
int		is_token(char c);
char	*null_increment(char *s);
char	*null_whitespace(char *s);
void	set_type(t_cmd *cmd);
int		count_parameters(t_cmd *cmd);

//Redirections
t_cmd	*create_redirs(t_cmd *cmd, t_data *data);
t_cmd	*handle_heredocs(t_cmd *cmd, t_data *data);
t_cmd	*handle_infiles(t_cmd *cmd);
t_cmd	*handle_outfiles(t_cmd *cmd);

//Signals
void	set_rl_signals(void);
void	set_exec_signals(void);
void	unset_signals(void);

//Utils
char	*combine_pathprog(char *path, char *prog);
char	*multijoin(bool tofrn, int n, ...);
void	free_multiple(int n, ...);
void	*free_ptr_array(void **array);
void	*ft_free(void *pointer);
char	*skip_space(char *ptr);
char	*skip_word(char *s);
char	*skip_argument(char *s);
int		is_word(char c);
int		is_token(char c);
int		ft_strcmp(char *s1, char *s2);
int		arraycount(char **array);
char	*get_word(char	*s);
char	*ft_last_word(const char *str, char c, int rev);
char	*multijoin_array(char **array);
int		is_valid_var(char *var);
int		is_var(char *s);
char	*skip_var(char *s);
char	*get_terminator(char *s);
char	*alloc_var_name(char *s);
#endif
