/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorhandling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 09:29:07 by rbetz             #+#    #+#             */
/*   Updated: 2022/12/27 17:33:49 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errorhandling.h"

/*Prints Minishell/function:filename:message/strerror to stderr and returns 1.*/
int	ft_error(char *function, char *filename, int ernum)
{
	if (function == NULL)
		ft_putstr_fd("minishell: ", 2);
	else
	{
		ft_putstr_fd(function, 2);
		ft_putstr_fd(": ", 2);
	}
	if (ernum == 1 || ernum == 2)
		perror(filename);
	else if (filename != NULL)
	{
		ft_putstr_fd(filename, 2);
		ft_putstr_fd(": ", 2);
	}
	if (ernum == 3)
		ft_putstr_fd("too many arguments\n", 2);
	else if (ernum == 4)
		ft_putstr_fd("not enough arguments\n", 2);
	else if (ernum == 5)
		ft_putstr_fd("illegal option\n", 2);
	else if (ernum == 6)
		ft_putstr_fd("not a valid identifier\n", 2);
	else if (ernum == 8)
		ft_putstr_fd("empty environment\n", 2);
	else if (ernum == 9)
		ft_putstr_fd("duplication error\n", 2);
	else if (ernum == 10)
	{
		ft_putstr_fd("syntax error\n", 2);
		ernum = 2;
	}
	else if (ernum == 11)
	{
		ft_putstr_fd("filename argument required\n", 2);
		ernum = 2;
	}
	else if (ernum == 126)
		ft_putstr_fd("is a directory\n", 2);
	else if (ernum == 127)
		ft_putstr_fd("command not found127\n", 2);
	else if (ernum == 128)
		ft_putstr_fd("invalid argument to exit\n", 2);
	g_exit_status = ernum;
	return (g_exit_status);
}
