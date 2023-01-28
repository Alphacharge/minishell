/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humbi <humbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 18:50:50 by fkernbac          #+#    #+#             */
/*   Updated: 2023/01/28 14:54:28 by humbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Returns the allocated first word in string delimited by whitespace.*/
char	*get_word(char	*s)
{
	int		i;
	char	*word;

	i = 0;
	word = NULL;
	s = skip_space(s);
	if (s == NULL || s[0] == '\0')
		return (NULL);
	while (s[i] != '\0' && ft_isspace(s[i]) == 0)
		i++;
	word = ft_calloc(i + 1, sizeof(char));
	i = 0;
	while (s[i] != '\0' && ft_isspace(s[i]) == 0)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}
