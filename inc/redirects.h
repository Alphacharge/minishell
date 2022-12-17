/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humbi <humbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 09:36:01 by rbetz             #+#    #+#             */
/*   Updated: 2022/12/17 14:21:41 by humbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTS_H
# define REDIRECTS_H

# include "structs.h"
# include "parsing.h"
# include <readline/readline.h>

# define FD_UNUSED INT32_MIN
# define STDIN 0
# define STDOUT 1
# define READ 0
# define WRITE 1

t_cmd	*create_redirs(t_cmd *cmd);
void	close_both_fds(t_cmd *cmd);
void	close_both_rats(t_cmd *cmd);
t_cmd	*handle_heredocs(t_cmd *cmd);
t_cmd	*handle_infiles(t_cmd *cmd);
t_cmd	*handle_outfiles(t_cmd *cmd);

#endif
