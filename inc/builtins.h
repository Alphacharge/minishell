/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 09:39:46 by rbetz             #+#    #+#             */
/*   Updated: 2022/12/23 14:38:01 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <unistd.h>
# include <dirent.h>
# include "libft.h"
# include "environment.h"
# include "errorhandling.h"

int	cd(char **argv, t_env *env, t_prompt *prompt);
int	echo(char **argv);
int	env(char **argv, t_env *env);
int	shell_exit(char **argv);
int	export(int argc, char **argv, t_data *data);
int	pwd(char **argv);
int	unset(char **argv, t_data *data);

#endif
