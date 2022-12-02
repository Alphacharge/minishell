/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 16:50:07 by fkernbac          #+#    #+#             */
/*   Updated: 2022/12/02 23:57:03 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*Manipulates s so that every valid quote is overwritten.*/
void	overwrite_quotes(char *s)
{
	char	quote;
	char	*quoteless;

	quoteless = s;
	while (*s != 0)
	{
		while (*s != 0 && *s != '\'' && *s != '\"')
			*quoteless++ = *s++;
		if (*s == 0)
			break ;
		quote = *s++;
		while (*s != 0 && *s != quote)
			*quoteless++ = *s++;
		if (*s == 0)
			break ;
		s++;
	}
	*quoteless = '\0';
}

/*Reallocates s if quotes are found and returns cleaned up copy.*/
static char	*remove_quotes(char *s)
{
	char	*new;
	int		i;

	i = -1;
	overwrite_quotes(s);
	new = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (new == NULL)
		return (ft_error(NULL), free(s), NULL);
	while (s[++i] != '\0')
			new[i] = s[i];
	return (free(s), new);
}

/*Returns allocated string of executable name in s with path (if found).
Name string is freed.*/
static char	*add_path(char *s, t_env *env)
{
	char	**paths;
	char	*new;

	if (s == NULL)
		return (NULL);
	paths = get_path_var(env);
	new = get_path(paths, s);
	free_ptr_array((void **)paths);
	if (new == NULL)
		ft_error(s);
	free(s);
	return (new);
}

/*Creates a newly allocated argv array with cleaned up strings for use in
execve.*/
static char	**create_argv(t_cmd *cmd, t_env *env)
{
	char	**argv;
	t_param	*current;
	int		i;

	i = 1;
	current = cmd->param;
	argv = ft_calloc(count_parameters(cmd) + 2, sizeof(char *));
	if (argv == NULL)
		return (free_ptr_array((void **)argv), NULL);
	argv[0] = remove_quotes(expand_envvars(cmd->name, env));
	while (current != NULL)
	{
		argv[i] = remove_quotes(expand_envvars(current->arg, env));
		if (argv[i++] == NULL)
			break ;
		current = current->next;
	}
	if (cmd->type == EXEC)
		argv[0] = add_path(argv[0], env);
	argv[i] = NULL;
	return (argv);
}

t_cmd	*parse(char *s, t_env *env)
{
	t_cmd	*lst;
	t_cmd	*current;

	lst = input_to_lst(s, env);
	current = lst;
	while (current != NULL)
	{
		set_type(current);
		current->argv = create_argv(current, env);
		if (current->argv == NULL)
			return (free_cmds(lst), NULL);
	//clean up redirs too, not only argv
		current = current->pipe;
	}
	return (lst);
}
