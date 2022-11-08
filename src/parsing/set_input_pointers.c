/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_input_pointers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:20:54 by fkernbac          #+#    #+#             */
/*   Updated: 2022/11/08 16:20:36 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

//Counts number of space-separated words in input string.
static int	count_args(char *input)
{
	int	i;
	int	number_args;

	i = 0;
	number_args = 0;
	if (input == NULL)
		return (0);
	while (input[i] != '\0')
	{
		while (input[i] == ' ')
			i++;
		while (input[i] != ' ' && input[i] != '\0')
			i++;
		number_args++;
	}
	if (VERBOSE == 1)
		printf("counted %i arguments\n", number_args);
	return (number_args);
}

char	**set_input_pointers(char *input)
{
	int		i;
	char	**args;
	int		i_args;

	i = 0;
	i_args = 0;
	args = ft_calloc(count_args(input) + 1, sizeof(char *));
	if (args == NULL)
		return (NULL);
	while (input[i] != '\0')
	{
		while (input[i] == ' ')
			input[i++] = '\0';
		if (input[i] == '\0')
			break ;
		args[i_args] = input + i;
		i_args++;
		while (input[i] != ' ' && input[i] != '\0')
			i++;
	}
	i_args++;
	args[i_args] = NULL;
	return (args);
}
