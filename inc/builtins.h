/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 09:39:46 by rbetz             #+#    #+#             */
/*   Updated: 2022/12/23 13:15:51 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <unistd.h>
# include <dirent.h>
# include "libft.h"
# include "environment.h"
# include "errorhandling.h"

int		cd(char **argv, t_env *env, t_prompt *prompt);
int		echo(char **argv);
void	env(char **argv, t_env *env);
int		shell_exit(char **argv);
t_env	*export(int argc, char **argv, t_env *env);
int		pwd(char **argv);
t_env	*unset(char **argv, t_env *env);

#endif
