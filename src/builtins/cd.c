/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 14:23:11 by rbetz             #+#    #+#             */
/*   Updated: 2022/11/17 16:14:18 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <dirent.h>
#include "environment.h"
#include "libft.h"

void	update_pwd(char *var, t_env *env)
{
	t_env	*tmp;
	char	*old;

	tmp = env;
	while (tmp != NULL && !ft_strncmp(tmp->name, "PWD", 3))
		tmp = tmp->next;
	old = tmp->value;
	tmp = env;
	while (tmp != NULL && !ft_strncmp(tmp->name, "OLDPWD", 6))
		tmp = tmp->next;
	free(tmp->value);
	tmp->value = old;
	tmp = env;
	while (tmp != NULL && !ft_strncmp(tmp->name, "PWD", 3))
		tmp = tmp->next;
	tmp->value = multijoin(true, 2, var, tmp->value);
}

void	cd(int argc, char **argv, t_env *env)
{
	int	ret;

	ret = 0;
	if (argc == 1)
		ret = chdir("~");
	else if (argc == 2)
	{
		if (argv[1] != NULL && ft_strlen(argv[1]) > 0)
		ret = chdir(argv[1]);
	}
	else
	{
		write(2, "cd: string not in pwd: ", 23);
		if (argv[1] != NULL)
			write(2, argv[1], ft_strlen(argv[1]));
		write(2, "\n", 1);
	}
	if (ret == -1)
	{
		write(2, "cd: no such file or directory: ", 30);
		if (argv[1] != NULL)
			write(2, argv[1], ft_strlen(argv[1]));
		write(2, "\n", 1);
	}
	else
		update_pwd(argv[1], env);
}
