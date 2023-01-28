/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humbi <humbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 16:50:07 by fkernbac          #+#    #+#             */
/*   Updated: 2023/01/28 14:53:36 by humbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (*s == 0)
		return (ft_free(s));
	overwrite_quotes(s);
	new = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (new == NULL)
		return (ft_error("malloc", NULL, 1), free(s), NULL);
	while (s[++i] != '\0')
			new[i] = s[i];
	return (free(s), new);
}

/*Cleans up command name. If it is neither an absolute nor a relative path,
searches for executable in PATH directories.*/
int	find_executable(t_cmd *cmd)
{
	struct stat	info;

	set_type(cmd);
	if (cmd->type == BLTIN)
		return (0);
	stat(cmd->name, &info);
	if (S_ISDIR(info.st_mode) || ft_strcmp("~", cmd->name) == 0)
		return (ft_error(NULL, cmd->name, 126));
	if ((cmd->name[0] == '.' || cmd->name[0] == '/' ) && S_ISREG(info.st_mode))
	{
		if (access(cmd->name, F_OK) < 0 || access(cmd->name, X_OK) < 0)
			return (ft_error(NULL, cmd->name, 1));
		return (0);
	}
	cmd->argv[0] = get_path(cmd->name, cmd->data->env);
	if (cmd->argv[0] == NULL)
		return (cmd->argv[0] = cmd->name, ft_error(NULL, cmd->name, 127));
	cmd->name = ft_free(cmd->name);
	return (0);
}

/*Cleans empty strings in argv. Returns pointer to first string.*/
char	*remove_empty_fields(int argc, char **argv)
{
	int	i;
	int	empty;

	i = 0;
	while (i < argc)
	{
		if (argv[i] == NULL)
		{
			empty = i;
			while (argv[i] == NULL && i < argc)
				i++;
			if (i == argc)
				break ;
			argv[empty] = argv[i];
			argv[i] = NULL;
			i = empty;
		}
		i++;
	}
	return (argv[0]);
}

/*Creates a newly allocated argv array with cleaned up strings for use in
execve.*/
static char	**create_argv(t_cmd *cmd, t_data *data)
{
	t_param	*current;
	int		i;

	i = 1;
	current = cmd->param;
	cmd->argv = ft_calloc(count_parameters(cmd) + 2, sizeof(char *));
	if (cmd->argv == NULL)
		return (NULL);
	cmd->name = remove_quotes(expand_envvars(cmd->name, data));
	cmd->argv[0] = cmd->name;
	while (current != NULL)
	{
		cmd->argv[i++] = remove_quotes(expand_envvars(current->arg, data));
		current = current->next;
	}
	cmd->argv[i] = NULL;
	cmd->name = remove_empty_fields(count_parameters(cmd) + 1, cmd->argv);
	if (find_executable(cmd) != 0)
		return (free_ptr_array((void **) cmd->argv));
	return (cmd->argv);
}

t_cmd	*parse(char *s, t_data *data)
{
	t_cmd	*lst;
	t_cmd	*current_cmd;
	t_redir	*current_redir;

	lst = input_to_lst(s, data);
	current_cmd = lst;
	while (current_cmd != NULL)
	{
		current_cmd->argv = create_argv(current_cmd, data);
		if (current_cmd->argv == NULL)
			return (free_cmds(lst), NULL);
		current_redir = current_cmd->redir;
		while (current_redir != NULL)
		{
			current_redir->file = expand_envvars(current_redir->file, data);
			current_redir->file = remove_quotes(current_redir->file);
			current_redir = current_redir->next;
		}
		current_cmd = current_cmd->next;
	}
	return (lst);
}
