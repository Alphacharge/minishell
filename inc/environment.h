/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 09:22:49 by rbetz             #+#    #+#             */
/*   Updated: 2022/11/11 17:28:11 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include <stdlib.h>
# include "structs.h"
# include "libft.h"
# include "utils.h"

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

void	get_env(t_var *var, char **envp);

t_env	*extract_env(char **envp);
void	print_env(t_env *env, int fd);
void	delete_env(t_env *env);
char	**create_envp_from_env(t_env *env);
char	**get_path_var(t_env *env);
char	*get_path(char **paths, char *executable);

#endif