/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 17:26:11 by fkernbac          #+#    #+#             */
/*   Updated: 2023/02/13 17:27:17 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Appends a new t_redir node at the last t_redir node of cmd.*/
static void	append_redir(t_cmd *cmd, t_redir *r)
{
	t_redir	*current;

	current = cmd->redir;
	if (current == NULL)
	{
		cmd->redir = r;
		return ;
	}
	while (current != NULL && current->next != NULL)
		current = current->next;
	current->next = r;
}

/*Adds the first redirection found in s as new t_redir node to cmd.*/
char	*new_redir(t_cmd *cmd, char *s)
{
	t_redir	*r;

	r = ft_calloc(1, sizeof(t_redir));
	if (r == NULL)
		return (cmd->data->exitstatus = ft_error("malloc", NULL, 1), NULL);
	r->file = NULL;
	r->next = NULL;
	if (*s == '<' && *(s + 1) == '<')
		r->type = HERE;
	else if (*s == '>' && *(s + 1) == '>')
		r->type = APPEND;
	else if (*s == '<')
		r->type = INPUT;
	else
		r->type = OUTPUT;
	if ((*s == '<' && *(s + 1) == '<') || (*s == '>' && *(s + 1) == '>'))
		s = null_increment(s);
	s = null_increment(s);
	s = null_whitespace(s);
	if (is_token(*s) == true || *s == '\0')
		return (ft_free(r));
	r->file = s;
	append_redir(cmd, r);
	return (skip_argument(s));
}
