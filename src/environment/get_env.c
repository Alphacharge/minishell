/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 10:41:28 by rbetz             #+#    #+#             */
/*   Updated: 2022/11/11 09:58:34 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

/*creates a new node 4 the env link list*/
static t_env	*new_env(void)
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
	t_env	*tmp_prev;

	tmp = env;
	while (tmp != NULL)
	{
		free(tmp->name);
		free(tmp->value);
		tmp_prev = tmp;
		tmp = tmp->next;
		free(tmp_prev);
	}
}

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
	envp = ft_calloc(i, sizeof(char *));
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

// void	get_env(t_var *var, char **envp)
// {
// 	int		i;
// 	char	*line;
// 	char	**ptr;

// 	i = 0;
// 	line = envp[i];
// 	while (line != NULL)
// 	{
// 		if (!ft_strncmp(line, "PATH=", 5))
// 			var->path = ft_split(&line[5], ':');
// 		if (ft_strstr(line, "OLDPWD=") == NULL && 
// 			ft_strstr(line, "PWD=") != NULL)
// 			var->pwd = ft_substr(line, 4, ft_strlen(line));
// 		i++;
// 		line = envp[i];
// 	}
// 	if (var->path == NULL)
// 	{
// 		ptr = ft_calloc(1, sizeof(char **));
// 		line = ft_strdup(".");
// 		ptr[0] = line;
// 		var->path = ptr;
// 	}
// }

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
