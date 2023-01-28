/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humbi <humbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:36:51 by fkernbac          #+#    #+#             */
/*   Updated: 2023/01/28 14:54:40 by humbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Skips characters until it encounters whitespace, quote or token.*/
char	*skip_word(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && s[i] != '\'' && s[i] != '\"' \
		&& ft_isspace(s[i]) == 0 && is_token(s[i]) == 0)
		i++;
	return (s + i);
}

char	*skip_space(char *s)
{
	if (s == NULL)
		return (NULL);
	while (*s != '\0' && ft_isspace(*s))
		s++;
	return (s);
}

/*Skips one argument containing any amount of quotation marks.*/
char	*skip_argument(char *s)
{
	char	quote;

	while (*s != '\0' && ft_isspace(*s) == 0 && is_token(*s) == 0)
	{
		if (*s == '\"' || *s == '\'')
		{
			quote = *s++;
			while (*s != '\0' && *s != quote)
				s++;
			if (*s == quote)
				s++;
		}
		s = skip_word(s);
	}
	return (s);
}
