/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 09:46:33 by rbetz             #+#    #+#             */
/*   Updated: 2023/02/13 13:06:21 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*transfers the PATH variable in an double ** array*/
char	**get_path_var(t_env *env)
{
	char	**ptr;

	ptr = NULL;
	while (env != NULL)
	{
		if (env->name != NULL  && ft_strncmp(env->name, "PATH", 4) == 0)
		{
			ptr = ft_split(env->value, ':');
			break ;
		}
		env = env->next;
	}
	if (ptr == NULL)
		return (NULL);
	else
		return (ptr);
}

/*searchs the path for a programm*/
char	*get_path(char *executable, t_env *env)
{
	int		i;
	int		success;
	char	*test;
	char	**paths;

	i = 0;
	success = -1;
	paths = get_path_var(env);
	while (paths != NULL && paths[i] != NULL && success != 0)
	{
		test = multijoin(false, 3, paths[i], "/", executable);
		success = access(test, F_OK);
		if (success == -1)
			ft_free(test);
		i++;
	}
	free_ptr_array((void **)paths);
	if (success != 0)
		return (NULL);
	else
		return (test);
}
