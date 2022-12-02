/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 15:52:36 by fkernbac          #+#    #+#             */
/*   Updated: 2022/12/02 22:44:40 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*Returns pointer to first character after closing single quote or null byte.*/
static char	*skip_single_quotes(char *s)
{
	if (*s == '\'')
		s++;
	while (*s != '\0' && *s != '\'')
		s++;
	if (*s == '\'')
		s++;
	return (s);
}

/*Returns pointer to the first occurrence of a valid variable.*/
static char	*skip_to_var(char *s)
{
	int	double_quotes;

	double_quotes = -1;
	while (*s != '\0')
	{
		if (is_var(s) == 1)
			return (s);
		if (*s == '\"')
			double_quotes *= -1;
		else if (double_quotes == -1 && *s == '\'')
			s = skip_single_quotes(s);
		if (*s == '\0')
			break ;
		s++;
	}
	return (s);
}

/*Creates an array of pointers to variable values and input strings that can
be joined to a single string.*/
static char	**var_array(char *s, int n, t_env *env)
{
	int		i;
	char	*var_name;
	char	**array;

	i = 0;
	array = ft_calloc(n, sizeof (char *));
	if (array == NULL)
		return (NULL);
	while (*s != '\0')
	{
		if (is_var(s) == 0)
			array[i++] = s;
		s = skip_to_var(s);
		while (is_var(s) == 1)
		{
			s = null_increment(s);
			var_name = alloc_var_name(s);
			array[i++] = get_env_var(env, var_name);
			if (array[i - 1] == NULL)
				array[i - 1] = get_terminator(s);
			var_name = ft_free(var_name);
			s = skip_var(s);
		}
	}
	return (array);
}

/*Returns number of all needed strings for expansion. Returns 0 if no
variable is found.*/
static int	count_var_strings(char *s)
{
	int	n;
	int	env_var;

	n = 0;
	env_var = 0;
	while (*s != '\0')
	{
		if (is_var(s) == 0)
			n++;
		s = skip_to_var(s);
		if (*s == '\0')
			break ;
		s++;
		s = skip_var(s);
		env_var = 1;
		n++;
	}
	if (env_var == 0)
		return (0);
	return (n);
}

/*Receives a pointer to input and returns a newly allocated copy with
expanded variables.*/
char	*expand_envvars(char *s, t_env *env)
{
	char	**array;
	int		number_strings;
	int		i;
	char	*joined;

	i = 0;
	number_strings = count_var_strings(s);
	if (number_strings == 0)
		return (ft_strdup(s));
	array = var_array(s, number_strings, env);
	array[0] = ft_strdup(array[0]);
	i = 1;
	while (i < number_strings)
	{
		joined = array[0];
		array[0] = ft_strjoin(array[0], array[i++]);
		joined = ft_free(joined);
	}
	joined = array[0];
	ft_free(array);
	return (joined);
}
