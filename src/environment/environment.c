/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 09:47:16 by rbetz             #+#    #+#             */
/*   Updated: 2022/12/23 11:37:19 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

/*creates a new node 4 the env link list*/
t_env	*new_env(void)
{
	t_env	*env;

	env = ft_calloc(1, sizeof(t_env));
	if (env == NULL)
		return (NULL);
	else
		return (env);
}

/*frees the env link list*/
void	delete_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp != NULL)
	{
		tmp->name = ft_free(tmp->name);
		tmp->value = ft_free(tmp->value);
		tmp = tmp->next;
	}
	while (env != NULL)
	{
		tmp = env->next;
		free_multiple(1, &env);
		env = tmp;
	}
}

/*updates the env pointer of following cmds*/
void	update_env(t_cmd *cmd)
{
	t_env *env;

	env = cmd->env;
	cmd = cmd->next;
	while (cmd != NULL)
	{
		cmd->env = env;
		cmd = cmd->next;
	}
}

/*is printing env linklist to fd your choice*/
void	print_env(t_env *env, int fd)
{
	if (env == NULL)
		ft_error(NULL, "empty environment", NULL);
	else
	{
		while (env != NULL)
		{
			if (env->name != NULL)
				ft_putstr_fd(env->name, fd);
			ft_putstr_fd("=", fd);
			if (env->value != NULL)
				ft_putstr_fd(env->value, fd);
			ft_putstr_fd("\n", fd);
			env = env->next;
		}
	}
}

/*creates a char ** from the env linked list*/
char	**create_envp_from_env(t_env *env)
{
	int		i;
	t_env	*tmp;
	char	**envp;

	i = 0;
	tmp = env;
	while (tmp != NULL)
	{
		i++;
		tmp = tmp->next;
	}
	envp = ft_calloc(i + 1, sizeof(char *));
	envp[i] = NULL;
	i = 0;
	while (env != NULL)
	{
		envp[i] = multijoin(false, 3, env->name, "=", env->value);
		if (envp[i] == NULL)
			return (NULL);
		i++;
		env = env->next;
	}
	return (envp);
}

/*creates a linked list from the **envp*/
t_env	*extract_env(char **envp)
{
	t_env	*env;
	t_env	*tmp;
	int		i;

	env = new_env();
	tmp = env;
	i = 0;
	if (env == NULL || envp == NULL)
		return (NULL);
	while (envp[i] != NULL)
	{
		tmp->name = ft_first_word(envp[i], '=', 0);
		tmp->value = ft_first_word(envp[i], '=', 1);
		i++;
		if (envp[i] != NULL)
		{
			tmp->next = new_env();
			tmp = tmp->next;
		}
	}
	return (env);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	t_env	*my;
// 	int		i;

// 	if (argc == 1)
// 		i = argc;
// 	if (argv[0])
// 	{
// 		ft_putstr_fd(argv[0], 1);
// 		ft_putstr_fd("\n", 1);
// 	}
// 	my = extract_env(envp);
// 	print_env(my, 1);
// 	delete_env(my);
// 	// system("leaks a.out");
// 	return (0);
// }
