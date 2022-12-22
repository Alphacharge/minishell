/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 09:39:46 by rbetz             #+#    #+#             */
/*   Updated: 2022/12/21 11:51:42 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <unistd.h>
# include <dirent.h>
# include "libft.h"
# include "environment.h"
# include "errorhandling.h"

void	cd(char **argv, t_env *env, t_prompt *prompt);
void	echo(char **argv);
void	env(char **argv, t_env *env);
int		shell_exit(char **argv);
t_env	*export(int argc, char **argv, t_env *env);
int		pwd(char **argv);
t_env	*unset(char **argv, t_env *env);

#endif
