/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 14:23:11 by rbetz             #+#    #+#             */
/*   Updated: 2022/11/28 11:32:26 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <dirent.h>
#include "environment.h"
#include "libft.h"
#include "builtins.h"
#include "errorhandling.h"

/*change oldpwd to pwd and set new pwd*/
static t_env	*update_pwd(char *var, t_data *data)
{
	char	*dir;

	if (var != NULL && data->env != NULL)
	{
		dir = get_env_var(data->env, "PWD");
		dir = ft_strdup(dir);
		if (dir != NULL)
			data->env = set_env_var(data->env, "OLDPWD", dir);
		if (dir != NULL)
			dir = getcwd(NULL, 0);
		if (dir != NULL)
			data->env = set_env_var(data->env, "PWD", dir);
		free(data->prompt->dir);
		data->prompt->dir = ft_last_word(dir, '/', 0);
		free(data->prompt->prompt);
		data->prompt->prompt = multijoin(false, 8, GREEN, data->prompt->name, \
		RED, data->prompt->seperator, YELL, data->prompt->dir, \
		data->prompt->endl, WHITE);
	}
	return (data->env);
}

/*accepts 1 arg or no arg 4 home, needs env to change pwd*/
void	cd(int argc, char **argv, t_data *data)
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
		update_pwd(argv[1], data);
}
