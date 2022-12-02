/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 09:39:46 by rbetz             #+#    #+#             */
/*   Updated: 2022/12/02 19:24:00 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "environment.h"

void	cd(int argc, char **argv, t_env *env, t_prompt *prompt);
void	echo(int argc, char **argv);
void	env(int argc, char **argv, t_env *env);
int		shell_exit(char **argv);
t_env	*export(int argc, char **argv, t_env *env);
void	pwd(int argc, char **argv);
t_env	*unset(int argc, char **argv, t_env *env);

#endif
