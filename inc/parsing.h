/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 09:19:48 by rbetz             #+#    #+#             */
/*   Updated: 2022/12/02 22:50:28 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"
# include "structs.h"
# include "libft.h"

t_cmd	*parse(char *s, t_env *env);
char	*expand_envvars(char *s, t_env *env);
t_cmd	*input_to_lst(char *s, t_env *env);

//	PARSING UTILS
int		is_token(char c);
char	*null_increment(char *s);
char	*null_whitespace(char *s);
void	set_type(t_cmd *cmd);
int		count_parameters(t_cmd *cmd);

//	VARIABLE EXPANSION UTILS
int		is_var(char *s);
char	*skip_var(char *s);
char	*get_terminator(char *s);
char	*alloc_var_name(char *s);

#endif
