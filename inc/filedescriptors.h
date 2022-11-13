/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filedescriptors.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 09:33:43 by rbetz             #+#    #+#             */
/*   Updated: 2022/11/13 20:05:14 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILEDESCRIPTORS_H
# define FILEDESCRIPTORS_H

# include <fcntl.h>
# include "libft.h"
# include "utils.h"
# include "errorhandling.h"
# include "minishell.h"
# include "structs.h"

void	check_infile(t_var *var, char **argv);
void	check_outfile(t_var *var, int argc, char **argv);
void	close_fds(t_var *var);
void	first_fd(t_var *var);

#endif
