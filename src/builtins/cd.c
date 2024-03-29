/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 14:23:11 by rbetz             #+#    #+#             */
/*   Updated: 2023/02/13 19:22:21 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Takes new working directory path and updates minishell prompt.*/
static void	update_prompt(char *pwd, t_prompt *prompt)
{
	free(prompt->dir);
	prompt->dir = ft_last_word(pwd, '/', 0);
	free(prompt->prompt);
	prompt->prompt = multijoin(false, 8, GREEN, prompt->name, \
		RED, prompt->seperator, YELL, prompt->dir, prompt->endl, WHITE);
}

static char	*my_getcwd(void)
{
	char	*dir;

	dir = getcwd(NULL, 0);
	if (dir == NULL)
	{
		ft_putstr_fd("cd: error retrieving current directory: getcwd: ", 2);
		ft_putstr_fd("cannot access parent directories: ", 2);
		ft_putstr_fd("No such file or directory\n", 2);
		dir = ft_strdup("");
	}
	return (dir);
}

/*change oldpwd to pwd and set new pwd*/
static t_env	*update_pwd(char *var, t_env *env, t_prompt *prompt)
{
	char	*dir;

	dir = NULL;
	if (var != NULL && env != NULL)
	{
		dir = get_env_var(env, "PWD");
		if (dir == NULL)
			return (env);
		if (dir != NULL)
			dir = ft_strdup(dir);
		if (dir == NULL)
			dir = my_getcwd();
		if (dir != NULL && get_env_var(env, "OLDPWD"))
			env = set_env_var(env, "OLDPWD", dir);
		else
			dir = ft_free(dir);
		dir = my_getcwd();
		if (dir != NULL)
			env = set_env_var(env, "PWD", dir);
		update_prompt(dir, prompt);
	}
	return (env);
}

/*accepts 1 arg or no arg 4 home, needs env to change pwd*/
int	cd(char **argv, t_env *env, t_prompt *prompt)
{
	int		ret;
	char	*dir;

	ret = 0;
	dir = argv[1];
	if (dir == NULL || ft_strcmp(dir, "~") == 0)
	{
		dir = get_env_var(env, "HOME");
		if (dir == NULL)
			return (ft_error("minishell: cd", dir, 5));
		ret = chdir(dir);
	}
	else if (argv[2] != NULL)
		return (ft_error("minishell: cd", NULL, 3));
	else if (ft_strlen(dir) > 0)
		ret = chdir(dir);
	if (ret == -1)
		return (ft_error("minishell: cd", dir, 1));
	else
		update_pwd(dir, env, prompt);
	return (0);
}
