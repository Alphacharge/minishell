/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 14:23:11 by rbetz             #+#    #+#             */
/*   Updated: 2022/12/08 09:42:05 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <dirent.h>
#include "environment.h"
#include "libft.h"
#include "builtins.h"
#include "errorhandling.h"

/*change oldpwd to pwd and set new pwd*/
static t_env	*update_pwd(char *var, t_env *env, t_prompt *prompt)
{
	char	*dir;

	if (var != NULL && env != NULL)
	{
		dir = get_env_var(env, "PWD");
		dir = ft_strdup(dir);
		if (dir != NULL)
			env = set_env_var(env, "OLDPWD", dir);
		if (dir != NULL)
			dir = getcwd(NULL, 0);
		if (dir != NULL)
			env = set_env_var(env, "PWD", dir);
		free(prompt->dir);
		prompt->dir = ft_last_word(dir, '/', 0);
		free(prompt->prompt);
		prompt->prompt = multijoin(false, 8, GREEN, prompt->name, \
			RED, prompt->seperator, YELL, prompt->dir, prompt->endl, WHITE);
	}
	return (env);
}

static void	message(char *custom, char *argv)
{
	if (custom != NULL)
		write(2, custom, ft_strlen(custom));
	if (argv != NULL)
		write(2, argv, ft_strlen(argv));
	write(2, "\n", 1);
}

/*accepts 1 arg or no arg 4 home, needs env to change pwd*/
void	cd(int argc, char **argv, t_env *env, t_prompt *prompt)
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
		message("cd: string not in pwd: ", argv[1]);
	if (ret == -1)
		message("cd: no such file or directory: ", argv[1]);
	else
		update_pwd(argv[1], env, prompt);
}
