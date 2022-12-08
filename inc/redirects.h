/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 09:36:01 by rbetz             #+#    #+#             */
/*   Updated: 2022/12/08 15:26:51 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTS_H
# define REDIRECTS_H

# include "structs.h"
# include "parsing.h"
# include <readline/readline.h>

// int	open_redir(t_cmd *cmd, t_env *env);
// int	close_redir(t_cmd *cmd);
t_cmd *create_redirs(t_cmd *cmd);
#endif
