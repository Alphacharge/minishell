/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 09:46:33 by rbetz             #+#    #+#             */
/*   Updated: 2022/11/14 09:46:55 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

/*transfers the PATH variable in an double ** array*/
char	**get_path_var(t_env *env)
{
	int		i;
	char	**ptr;

	while (env != NULL)
	{
		if (ft_strncmp(env->name, "PATH", 4))
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
char	*get_path(char **paths, char *executable)
{
	int		i;
	int		success;
	char	*test;

	i = 0;
	success = -1;
	while (paths != NULL && paths[i] != NULL && success != 0)
	{
		test = multijoin(false, 2, paths[i], executable);
		success = access(test, F_OK);
		if (success == -1)
			free(test);
		i++;
	}
	if (success == 0)
		return (paths[--i]);
	else
		return (NULL);
}