/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 09:47:16 by rbetz             #+#    #+#             */
/*   Updated: 2022/11/29 14:49:40 by rbetz            ###   ########.fr       */
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
#include <stdio.h>
/*frees the env link list*/
void	delete_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	// print_env(env, 2);
	while (tmp != NULL)
	{
		// printf("Line\t%s\n", tmp->name);
		//error here with double freeing pwd
		free_multiple(1, &tmp->name);
		tmp->name = NULL;
		free_multiple(1, &tmp->value);
		tmp->value = NULL;
		tmp = tmp->next;
	}
	while (env != NULL)
	{
		tmp = env->next;
		free_multiple(1, &env);
		env = tmp;
	}
}
// t_env	*tmp;
	//
	// tmp = env;
	// while (tmp != NULL)
	// {
		// if (tmp->name != NULL)
			// free(tmp->name);
		// if (tmp->value != NULL)
			// free(tmp->value);
		// tmp->name = NULL;
		// tmp->value = NULL;
		// tmp = tmp->next;
	// }
	// while (env != NULL)
	// {
		// if (env->next != NULL)
			// tmp = env->next;
		// free(env);
		// env = tmp;
	// }

/*is printing env linklist to fd your choice*/
void	print_env(t_env *env, int fd)
{
	if (env == NULL)
		ft_putstr_fd("Error, empty Environment", fd);
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

/*returns a pointer to the value of a env variable*/
char	*get_env_var(t_env *env, char *name)
{
	while (env != NULL)
	{
		if (ft_strcmp(name, env->name) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

/*sets a variable to a new value, if the var not exist it returns NULL*/
t_env	*set_env_var(t_env *env, char *name, char *value)
{
	t_env	*head;

	head = env;
	if (env == NULL || name == NULL || value == NULL)
		return (head);
	while (env != NULL && ft_strcmp(env->name, name) != 0)
		env = env->next;
	if (env != NULL)
	{
		// printf("%s\n", env->value);
		free_multiple(1, &env->value);
		env->value = value;
	// printf("%s\n", env->value);
	}
	return (head);
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
