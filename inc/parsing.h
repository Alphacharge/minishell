/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 09:19:48 by rbetz             #+#    #+#             */
/*   Updated: 2022/12/01 17:02:26 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"
# include "structs.h"
# include "libft.h"

// void	parse_progs(t_var *var, char **argv, char **envp);
// void	parse_args(t_var *var, int argc, char **argv, char **envp);
// t_cmd	*str_to_lst(char *input, t_env *env);
t_cmd	*parse(char *s, t_env *env);
void	set_type(t_cmd *cmd);
char	*null_increment(char *s);
void	set_type(t_cmd *cmd);
char	*expand_envvars(char *s, t_env *env);
char	**create_argv(t_cmd *cmd, t_env *env);
t_cmd	*input_to_lst(char *s, t_env *env);

#endif
