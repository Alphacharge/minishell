/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 09:19:48 by rbetz             #+#    #+#             */
/*   Updated: 2023/01/28 13:06:31 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <sys/stat.h>
// # include "minishell.h"
# include "structs.h"
# include "utils.h"
# include "libft.h"

t_cmd	*parse(char *s, t_data *data);
char	*expand_envvars(char *s, t_data *data);
t_cmd	*input_to_lst(char *s, t_data *data);

//	PARSING UTILS
int		is_token(char c);
char	*null_increment(char *s);
char	*null_whitespace(char *s);
void	set_type(t_cmd *cmd);
int		count_parameters(t_cmd *cmd);

#endif
