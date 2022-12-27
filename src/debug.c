/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 11:52:16 by fkernbac          #+#    #+#             */
/*   Updated: 2022/12/24 11:52:33 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cmds(t_cmd *lst)
{
	t_param	*param;
	t_redir	*redir;
	int		i;

	i = 0;
	printf("\n-------------------\n");
	while (lst != NULL)
	{
		param = lst->param;
		redir = lst->redir;
		if (lst->name != NULL)
			printf("name: %s\n", lst->name);
		while (param != NULL)
		{
			printf("param: %s\n", param->arg);
			param = param->next;
		redir = lst->redir;
		}
		while (redir != NULL)
		{
			printf("redir: %s\n", redir->file);
			redir = redir->next;
		}
		printf("argv: ");
		while (lst->argv != NULL && lst->argv[i] != NULL)
			printf("|%s| ", lst->argv[i++]);
		printf("\n");
		if (lst->next != NULL)
			printf("---pipe-->\n");
		i = 0;
		lst = lst->next;
	}
	printf("-------------------\n");
}
