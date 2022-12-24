/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 09:22:49 by rbetz             #+#    #+#             */
/*   Updated: 2022/12/24 10:48:05 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include <stdlib.h>
# include "structs.h"
# include "libft.h"
# include "utils.h"

# define RED	"\x01\033[1;31m\x02"
# define GREEN	"\x01\033[1;32m\x02"
# define YELL	"\x01\033[1;33m\x02"
# define BLUE	"\x01\033[1;34m\x02"
# define WHITE	"\x01\033[0m\x02"

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

t_env	*extract_env(char **envp);
void	print_env(t_env *env, int fd);
void	delete_env(t_env *env);
char	**create_envp_from_env(t_env *env);
char	**get_path_var(t_env *env);
char	*get_path(char *executable, t_env *env);
char	*get_env_var(t_env *env, char *name);
t_env	*set_env_var(t_env *env, char *name, char *value);
t_env	*new_env(void);

#endif
