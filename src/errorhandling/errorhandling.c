/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorhandling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 09:29:07 by rbetz             #+#    #+#             */
/*   Updated: 2023/02/10 12:59:53 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Bash special exit codes.*/
static int	exitcode_bash(int ernum)
{
	if (ernum == 3)
		ft_putstr_fd("too many arguments\n", 2);
	else if (ernum == 6)
		ft_putstr_fd("not a valid identifier\n", 2);
	else if (ernum == 10)
		ft_putstr_fd("syntax error\n", 2);
	else if (ernum == 11)
		ft_putstr_fd("filename argument required\n", 2);
	else if (ernum == 128 || ernum == 255)
		ft_putstr_fd("invalid argument to exit\n", 2);
	if (ernum == 3 || ernum == 6)
		return (1);
	if (ernum == 10 || ernum == 11)
		return (2);
	if (ernum == 128)
		return (255);
	return (ernum);
}

/*Minishell custom exit codes.*/
static int	exitcode_custom(int ernum)
{
	if (ernum == 4)
		ft_putstr_fd("not enough arguments\n", 2);
	else if (ernum == 5)
		ft_putstr_fd("illegal option\n", 2);
	else if (ernum == 8)
		ft_putstr_fd("empty environment\n", 2);
	else if (ernum == 9)
		ft_putstr_fd("duplication error\n", 2);
	else if (ernum == 126)
		ft_putstr_fd("is a directory\n", 2);
	else if (ernum == 127)
		ft_putstr_fd("command not found\n", 2);
	else
		ernum = exitcode_bash(ernum);
	return (ernum);
}

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
	ernum = exitcode_custom(ernum);
	return (ernum);
}

/*Writes errorcode into data struct and prints error message.*/
int	set_error(char *function, char *filename, int ernum, t_data *data)
{
	data->exitstatus = ft_error(function, filename, ernum);
	return (data->exitstatus);
}
