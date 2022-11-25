/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 09:39:46 by rbetz             #+#    #+#             */
/*   Updated: 2022/11/25 10:41:51 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "environment.h"

void	cd(char **argv, t_env *env);
void	echo(int argc, char **argv);
void	env(int argc, char **argv, t_env *env);
int		shell_exit(char **argv);
t_env	*export(int argc, char **argv, t_env *env);
// t_env	*export(char *name, char *value, t_env *env);
void	pwd(int argc, char **argv);
t_env	*unset(int argc, char **argv, t_env *env);
// t_env	*unset(char *var, t_env *env);


#endif
