/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 20:07:04 by fkernbac          #+#    #+#             */
/*   Updated: 2023/02/07 20:10:34 by fkernbac         ###   ########.fr       */
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

/*Returns first character after closed double quotes.*/
char	*skip_quotes(char *s, int *quotes)
{
	while (*s == '\"' || *s == '\'')
	{
		while (*s == '\"')
		{
			*quotes *= -1;
			s++;
		}
		while (*s == '\'' && *quotes == -1)
			s = skip_single_quotes(s);
		while (*s == '\'' && *quotes == 1)
			s++;
	}
	return (s);
}

/*Returns pointer to next variable or quote character.*/
char	*skip_to_var_token(char *s)
{
	while (*s != '\0')
	{
		if (is_var(s) == 1 || *s == '\'' || *s == '\"')
			return (s);
		s++;
	}
	return (s);
}
