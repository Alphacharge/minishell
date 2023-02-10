/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 15:52:36 by fkernbac          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/02/08 17:10:43 by rbetz            ###   ########.fr       */
=======
/*   Updated: 2023/02/09 19:27:31 by fkernbac         ###   ########.fr       */
>>>>>>> origin/fk_bugfix
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Returns non-allocated pointer to value of given variable name.*/
static char	*pointer_to_var(char *s, t_env *env, char *exitstatus)
{
	char	*var_name;
	char	*var_value;

	if (*s == '?')
		return (exitstatus);
	var_name = alloc_var_name(s);
	var_value = get_env_var(env, var_name);
	if (var_value == NULL)
		var_value = get_terminator(s);
	var_name = ft_free(var_name);
	return (var_value);
}

static void	fill_var_array(char *s, char **array, t_env *env, char *exitstatus)
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
			array[i++] = pointer_to_var(s, env, exitstatus);
			s = skip_var(s);
			if (is_var(s) == 0 && *s != 0)
				array[i++] = s;
		}
	}
	array[i] = NULL;
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
char	*expand_envvars(char *input, t_data *data)
{
	char	**array;
	int		number_strings;
	char	*s_temp;

	s_temp = input;
	if (input == NULL)
		return (NULL);
	while (*s_temp != 0 && is_var(s_temp) == 0)
		s_temp++;
	if (*s_temp == 0)
		return (ft_strdup(input));
	number_strings = count_var_strings(input);
	if (number_strings == 0)
		return (ft_strdup(input));
	array = ft_calloc(number_strings + 1, sizeof (char *));
	if (array == NULL)
		return (NULL);
	s_temp = ft_itoa(data->exitstatus);
	fill_var_array(input, array, data->env, s_temp);
	input = multijoin_array(array);
	ft_free(s_temp);
	return (input);
}
