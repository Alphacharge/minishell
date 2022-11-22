/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 14:23:11 by rbetz             #+#    #+#             */
/*   Updated: 2022/11/22 14:32:50 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <dirent.h>
#include "environment.h"
#include "libft.h"
#include "builtins.h"
#include "errorhandling.h"

// static void	update_pwd(char *var, t_env *env)
// {
// 	t_env	*tmp;
// 	char	*old;
// // needs to be changed :D function from env and export
// 	tmp = env;
// 	while (tmp != NULL && ft_strcmp(tmp->name, "PWD"))
// 		tmp = tmp->next;
// 	old = tmp->value;
// 	tmp = env;
// 	while (tmp != NULL && ft_strcmp(tmp->name, "OLDPWD"))
// 		tmp = tmp->next;
// 	ft_free(tmp->value);
// 	tmp->value = old;
// 	tmp = env;
// 	while (tmp != NULL && !ft_strcmp(tmp->name, "PWD"))
// 		tmp = tmp->next;
// 	//Invalid free is under this line
// 	old = tmp->value;
// 	//wrong absolut path
// 	tmp->value = multijoin(false, 2, var, tmp->value);
// 	old = ft_free(old);
// }
static t_env	*update_pwd(char *var, t_env *env)
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
	}
	return (env);
}

/*accepts 1 arg or no arg 4 home, needs env to change pwd*/
void	cd(char **argv, t_env *env)
{
	int	ret;

	ret = 0;
	if (argv[1] == NULL)
		ret = chdir(get_env_var(env, "HOME"));
	else if (argv[2] != NULL)
	{
		printf("cd: too many arguments\n");
		return ;
	}
	else if (argv[1][0] > 0)
		ret = chdir(argv[1]);
	if (ret == -1)
	{
		ft_error("minishell: cd:");
		// if (argv[1] != NULL)
		// 	write(2, argv[1], ft_strlen(argv[1]));
		write(2, "\n", 1);
	}
	else
		update_pwd(argv[1], env);
}
