/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 15:52:36 by fkernbac          #+#    #+#             */
/*   Updated: 2022/12/01 17:13:05 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*Returns pointer to first character after closing single quote or null byte.*/
char	*skip_single_quotes(char *s)
{
	if (*s == '\'')
		s++;
	while (*s != '\0' && *s != '\'')
		s++;
	if (*s == '\'')
		s++;
	return (s);
}

/*Returns 1 if sequence at start of s is a valid shell variable.*/
int	is_var(char *s)
{
	if (*s == '$' && (ft_isalpha(*(s + 1)) == 1 || *(s + 1) == '_'))
		return (1);
	return (0);
}

/*Returns pointer to the first occurrence of a valid variable.*/
char	*skip_to_var(char *s)
{
	while (*s != '\0')
	{
		if (is_var(s) == 1)
			return (s);
		if (*s == '\'')
			s = skip_single_quotes(s);
		if (*s == '\0')
			break ;
		s++;
	}
	return (s);
}

char	*skip_var(char *s)
{
	while (*s != '\0' && (ft_isalnum(*s) || *s == '_'))
		s++;
	return (s);
}

/*Allocates the name of s until the first invalid character for searching
in environment data.*/
char	*alloc_var_name(char *s)
{
	int		l;
	int		i;
	char	*name;

	l = 0;
	i = 0;
	while (s[l] != '\0' && (ft_isalnum(s[l]) == 1 || s[l] == '_'))
		l++;
	name = ft_calloc(l + 1, sizeof(char));
	if (name == NULL)
		return (NULL);
	while (i < l)
	{
		name[i] = s[i];
		i++;
	}
	return (name);
}

/*Returns pointer to the first nullbyte character in s.*/
char	*get_terminator(char *s)
{
	while (*s != '\0')
		s++;
	return (s);
}

char	**var_array(char *s, int n, t_env *env)
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
int	count_var_strings(char *s)
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

char	*expand_envvars(char *s, t_env *env)
{
	char	**array;
	int		number_strings;
	int		i;
	char	*temp;
	char	*not_expanded;

	i = 0;
	not_expanded = s;
	number_strings = count_var_strings(s);
	if (number_strings == 0)
		return (s);
	array = var_array(s, number_strings, env);
	array[0] = ft_strdup(array[0]);
	i = 1;
//we could implement a pointer array multijoin for this
	while (i < number_strings)
	{
		temp = array[0];
		array[0] = ft_strjoin(array[0], array[i]);
		temp = ft_free(temp);
		i++;
	}
	temp = array[0];
	ft_free(not_expanded);
	ft_free(array);
	return (temp);
}
