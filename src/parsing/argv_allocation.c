/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameters.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 16:47:23 by fkernbac          #+#    #+#             */
/*   Updated: 2022/12/01 16:48:27 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	count_parameters(t_cmd *cmd)
{
	t_param	*current;
	int		n;

	current = cmd->param;
	n = 0;
	while (current != NULL)
	{
		n++;
		current = current->next;
	}
	return (n);
}

char	*arg_to_argv(char *s)
{
	int		i;
	char	*argument;

	i = 0;
	argument = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (argument == NULL)
		return (NULL);
	while (s[i] != 0)
	{
		argument[i] = s[i];
		i++;
	}
	return (argument);
}

/*Returns allocated string of executable name with path (if found).*/
char	*add_path(char *name, t_env *env)
{
	char	**paths;
	char	*new;

	paths = get_path_var(env);
	new = get_path(paths, name);
	free_ptr_array((void **)paths);
	if (new == NULL)
		return (printf("minishell: %s: command not found\n", name), NULL);
	return (new);
}

char	**create_argv(t_cmd *cmd, t_env *env)
{
	char	**argv;
	t_param	*current;
	int		i;

	i = 1;
	(void)env;
	current = cmd->param;
	argv = ft_calloc(count_parameters(cmd) + 2, sizeof(char *));
	if (argv == NULL)
		return (NULL);
	if (cmd->type == EXEC)
		argv[0] = add_path(cmd->name, env);
	else
		argv[0] = ft_strdup(cmd->name);
	if (argv[0] == NULL)
		return (free_ptr_array((void **)argv), NULL);
	while (current != NULL)
	{
		argv[i] = arg_to_argv(current->arg);
		argv[i] = expand_envvars(argv[i], env);
		// argv[i] = remove_quotes(argv[i]);
		current = current->next;
		i++;
	}
	argv[i] = NULL;
	return (argv);
}
