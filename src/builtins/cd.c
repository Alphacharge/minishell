/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 14:23:11 by rbetz             #+#    #+#             */
/*   Updated: 2022/12/21 11:50:16 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

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

/*accepts 1 arg or no arg 4 home, needs env to change pwd*/
void	cd(char **argv, t_env *env, t_prompt *prompt)
{
	int	ret;

	ret = 0;
	if (argv[1] == NULL)
		ret = chdir("~");
	else if (argv[2] != NULL)
		ft_error(NULL, "cd", "too many arguments");
	else if (ft_strlen(argv[1]) > 0)
		ret = chdir(argv[1]);
	if (ret == -1)
		ft_error("minishell: cd", argv[1], NULL);
	else
		update_pwd(argv[1], env, prompt);
}
