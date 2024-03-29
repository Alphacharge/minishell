/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 22:14:56 by fkernbac          #+#    #+#             */
/*   Updated: 2023/02/10 14:22:40 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Returns 1 if sequence at start of s is a valid shell variable.*/
int	is_var(char *s)
{
	if (*s == '$' \
		&& (ft_isalpha(*(s + 1)) == 1 || *(s + 1) == '_' || *(s + 1) == '?'))
		return (1);
	return (0);
}

/*Skips to first character that is not part of variable name.*/
char	*skip_var(char *s)
{
	if (*s == '$')
		s++;
	if (*s == '?')
		return (++s);
	while (*s != '\0' && (ft_isalnum(*s) || *s == '_' || *s == '?'))
		s++;
	return (s);
}

/*Returns pointer to the first nullbyte character in s.*/
char	*get_terminator(char *s)
{
	while (*s != '\0')
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
	if (*s == '$')
		s++;
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
