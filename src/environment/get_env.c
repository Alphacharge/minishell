/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 10:41:28 by rbetz             #+#    #+#             */
/*   Updated: 2022/11/09 16:29:40 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

static t_env	*new_env(void)
{
	t_env	env;
	
	env = ft_calloc(1, sizeof(t_env));
	if (env == NULL)
		return (NULL);
	else
		return (env);
}

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
			if (env->name != NULL)
				ft_putstr_fd(env->name, fd);
			env = env->next;
		}
	}
}

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

void	get_env(t_var *var, char **envp)
{
	int		i;
	char	*line;
	char	**ptr;

	i = 0;
	line = envp[i];
	while (line != NULL)
	{
		if (!ft_strncmp(line, "PATH=", 5))
			var->path = ft_split(&line[5], ':');
		if (ft_strstr(line, "OLDPWD=") == NULL && \
			ft_strstr(line, "PWD=") != NULL)
			var->pwd = ft_substr(line, 4, ft_strlen(line));
		i++;
		line = envp[i];
	}
	if (var->path == NULL)
	{
		ptr = ft_calloc(1, sizeof(char **));
		line = ft_strdup(".");
		ptr[0] = line;
		var->path = ptr;
	}
}

int main(int argc, char **argv, char **envp)
{
	if (argc == 1)
		ft_putstr_fd("1\n", 1);
	if (argv[0])
		ft_putstr_fd(argv[0], 1);
		ft_putstr_fd("\n", 1);
	t_env	*my;
	my = extract_env(envp);
	print_env(my);
	delete_env(my);
	system("leaks a.out");
	return (0);
}