/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 18:42:16 by fkernbac          #+#    #+#             */
/*   Updated: 2023/02/09 10:27:22 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Manipulates s so that every valid quote is overwritten.*/
void	overwrite_quotes(char *s)
{
	char	quote;
	char	*quoteless;

	quoteless = s;
	while (*s != 0)
	{
		while (*s != 0 && *s != '\'' && *s != '\"')
			*quoteless++ = *s++;
		if (*s == 0)
			break ;
		quote = *s++;
		while (*s != 0 && *s != quote)
			*quoteless++ = *s++;
		if (*s == 0)
			break ;
		s++;
	}
	*quoteless = '\0';
}

/*Reallocates s if quotes are found and returns cleaned up copy.*/
char	*remove_quotes(char *s)
{
	char	*new;
	int		i;

	i = -1;
	if (s == NULL)
		return (NULL);
	if (*s == '\0')
		return (ft_free(s));
	overwrite_quotes(s);
	new = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (new == NULL)
		return (ft_error("malloc", NULL, 1), free(s), NULL);
	while (s[++i] != '\0')
			new[i] = s[i];
	return (free(s), new);
}
