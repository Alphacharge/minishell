/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 16:50:07 by fkernbac          #+#    #+#             */
/*   Updated: 2022/12/23 14:12:09 by rbetz            ###   ########.fr       */
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
		return (ft_error("malloc", NULL, NULL), free(s), NULL);
	while (s[++i] != '\0')
			new[i] = s[i];
	return (free(s), new);
}

/*Cleans up command name. If it is neither an absolute nor a relative path,
searches for executable in PATH directories.*/
int	parse_name(t_cmd *cmd, t_data *data)
{
	cmd->name = remove_quotes(expand_envvars(cmd->name, data));
	cmd->argv[0] = ft_strdup(cmd->name);
	set_type(cmd);
	if (cmd->type == BLTIN)
		return (0);
	if (cmd->name[0] == '.' || cmd->name[0] == '/')
	{
		if (access(cmd->name, F_OK) < 0 || access(cmd->name, X_OK) < 0)
			return (ft_free(cmd->argv[0]), ft_error(NULL, cmd->name, NULL), -1);
		return (0);
	}
	cmd->argv[0] = ft_free(cmd->argv[0]);
	cmd->argv[0] = get_path(cmd->name, cmd->data->env);
	if (cmd->argv[0] == NULL)
		return (ft_error(NULL, cmd->name, "command not found"), -1);
	return (0);
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
	if (parse_name(cmd, data) < 0)
		return (ft_free(cmd->argv));
	while (current != NULL)
	{
		cmd->argv[i] = remove_quotes(expand_envvars(current->arg, data));
		if (cmd->argv[i++] == NULL)
			break ;
		current = current->next;
	}
	cmd->argv[i] = NULL;
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
