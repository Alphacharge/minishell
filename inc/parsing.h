/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 09:19:48 by rbetz             #+#    #+#             */
/*   Updated: 2022/11/17 16:33:39 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "structs.h"
# include "libft.h"
# include "minishell.h"

// void	parse_progs(t_var *var, char **argv, char **envp);
// void	parse_args(t_var *var, int argc, char **argv, char **envp);
t_cmd	*str_to_lst(char *input, t_env *env);

#endif
