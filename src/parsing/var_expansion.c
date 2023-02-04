/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 15:52:36 by fkernbac          #+#    #+#             */
/*   Updated: 2023/02/04 16:07:00 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Returns pointer to first character after closing single quote or null byte.*/
static char	*skip_single_quotes(char *s)
{
	if (*s == '\'')
		s++;
	else
		return (s);
	while (*s != '\0' && *s != '\'')
		s++;
	if (*s == '\'')
		s++;
	return (s);
}

/*Returns pointer to next variable or quote character.*/
static char	*skip_to_var_token(char *s)
{
	while (*s != '\0')
	{
		if (is_var(s) == 1 || *s == '\'' || *s == '\"')
			return (s);
		s++;
	}
	return (s);
}

/*Creates an array of pointers to variable values and input strings that can
be joined to a single string.*/
static char	**var_array(char *s, int n, t_data *data)
{
	int		i;
	char	*var_name;
	char	**array;
	int		quotes;

	i = 0;
	quotes = -1;
	data->exitstatus = ft_itoa(g_exit_status);
	array = ft_calloc(n + 1, sizeof (char *));
	if (array == NULL)
		return (NULL);
	if (is_var(s) == 0)
		array[i++] = s;
	while (*s != 0)
	{
		s = skip_to_var_token(s);
		while (*s == '\"')
		{
			quotes *= -1;
			s++;
		}
		while (*s == '\'' && quotes == -1)
			s = skip_single_quotes(s);
		while (*s == '\'' && quotes == 1)
			s++;
		if (is_var(s) == 1)
		{
			while (is_var(s) == 1)
			{
				s = null_increment(s);
				if (*s == '?')
					array[i] = data->exitstatus;
				else
				{
					var_name = alloc_var_name(s);
					array[i] = get_env_var(data->env, var_name);
					if (array[i] == NULL)
						array[i] = get_terminator(s);
					var_name = ft_free(var_name);
				}
				i++;
				s = skip_var(s);
			}
			if (*s != 0)
				array[i++] = s;
		}
	}
	array[i] = NULL;
	return (array);
}

/*Returns number of all needed strings for expansion.*/
static int	count_var_strings(char *s)
{
	int	n;
	int	quotes;

	n = 1;
	if (is_var(s) == 1)
		n = 0;
	quotes = -1;
	while (*s != '\0')
	{
		s = skip_to_var_token(s);
		while (*s == '\"')
		{
			quotes *= -1;
			s++;
		}
		while (*s == '\'' && quotes == -1)
			s = skip_single_quotes(s);
		while (*s == '\'' && quotes == 1)
			s++;
		if (is_var(s) == 1)
		{
			while (is_var(s) == 1)
			{
				s = skip_var(s);
				n++;
			}
			if (*s != 0)
				n++;
		}
	}
	return (n);
}

/*Receives a pointer to input and returns a newly allocated copy with
expanded variables.*/
char	*expand_envvars(char *s, t_data *data)
{
	char	**array;
	int		number_strings;
	char	*search;

	search = s;
	if (s == NULL)
		return (NULL);
	while (*search != 0 && is_var(search) == 0)
		search++;
	if (*search == 0)
		return (ft_strdup(s));
	number_strings = count_var_strings(s);
	if (number_strings == 0)
		return (ft_strdup(s));
	array = var_array(s, number_strings, data);
	return (multijoin_array(array));
}
