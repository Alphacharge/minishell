/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 14:23:11 by rbetz             #+#    #+#             */
/*   Updated: 2022/11/19 12:18:41 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <dirent.h>
#include "environment.h"
#include "libft.h"
#include "builtins.h"
#include "errorhandling.h"

static void	update_pwd(char *var, t_env *env)
{
	t_env	*tmp;
	char	*old;

	tmp = env;
	while (tmp != NULL && ft_strncmp(tmp->name, "PWD", 3) != 0)
		tmp = tmp->next;
	old = tmp->value;
	tmp = env;
	while (tmp != NULL && !ft_strncmp(tmp->name, "OLDPWD", 6))
		tmp = tmp->next;
//searching for freeing error
printf("update_pwd: freeing%p\n", tmp->value);
	ft_free(tmp->value);
	tmp->value = old;
	tmp = env;
	while (tmp != NULL && !ft_strncmp(tmp->name, "PWD", 3))
		tmp = tmp->next;
	tmp->value = multijoin(true, 2, var, tmp->value);
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
