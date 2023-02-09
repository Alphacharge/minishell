/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 16:50:07 by fkernbac          #+#    #+#             */
/*   Updated: 2023/02/09 10:28:29 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Cleans up command name. If it is neither an absolute nor a relative path,
searches for executable in PATH directories.*/
int	find_executable(t_cmd *cmd)
{
	struct stat	info;

	set_type(cmd);
	if (cmd->type == BLTIN)
		return (0);
	if ((stat(cmd->name, &info) == 0 && S_ISDIR(info.st_mode)) \
		|| ft_strcmp("~", cmd->name) == 0)
		return (ft_error(NULL, cmd->name, 126));
	// if (stat(cmd->name, &info) == 0 && S_ISREG(info.st_mode) 
	if (ft_posinset('/', cmd->name) > -1)
	{
		if (access(cmd->name, F_OK) < 0 || access(cmd->name, X_OK) < 0)
			return (ft_error(NULL, cmd->name, 127));
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
	if (cmd->name == NULL)
		return (ft_free(cmd->argv), NULL);
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
