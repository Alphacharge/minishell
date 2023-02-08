/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 15:52:36 by fkernbac          #+#    #+#             */
/*   Updated: 2023/02/08 17:10:43 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Returns non-allocated pointer to value of given variable name.*/
static char	*pointer_to_var(char *s, t_data *data)
{
	char	*var_name;
	char	*var_value;

	if (*s == '?')
		return (data->exitstatus);
	var_name = alloc_var_name(s);
	var_value = get_env_var(data->env, var_name);
	if (var_value == NULL)
		var_value = get_terminator(s);
	var_name = ft_free(var_name);
	return (var_value);
}

static void	fill_var_array(char *s, char **array, t_data *data)
{
	int		i;
	int		quote_status;

	i = 0;
	quote_status = -1;
	if (is_var(s) == 0)
		array[i++] = s;
	while (*s != 0)
	{
		s = skip_to_var_token(s);
		s = skip_quotes(s, &quote_status);
		if (is_var(s) == 1)
		{
			s = null_increment(s);
			array[i++] = pointer_to_var(s, data);
			s = skip_var(s);
			if (is_var(s) == 0 && *s != 0)
				array[i++] = s;
		}
	}
	array[i] = NULL;
}

/*Creates an array of pointers to variable values and input strings that can
be joined to a single string.*/
static char	**var_array(char *s, int n, t_data *data)
{
	char	**array;

	if (data->exitstatus != NULL)
		data->exitstatus = ft_free(data->exitstatus);
	data->exitstatus = ft_itoa(g_exit_status);
	array = ft_calloc(n + 1, sizeof (char *));
	if (array == NULL)
		return (NULL);
	fill_var_array(s, array, data);
	return (array);
}

/*Returns number of all needed strings for expansion.*/
static int	count_var_strings(char *s)
{
	int	n;
	int	quote_status;

	n = 1;
	quote_status = -1;
	if (is_var(s) == 1)
		n = 0;
	while (*s != '\0')
	{
		s = skip_to_var_token(s);
		s = skip_quotes(s, &quote_status);
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
