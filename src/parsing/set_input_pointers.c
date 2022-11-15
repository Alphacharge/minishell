/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_input_pointers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:20:54 by fkernbac          #+#    #+#             */
/*   Updated: 2022/11/15 11:14:14 by rbetz            ###   ########.fr       */
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
		while (ft_isspace(input[i]))
			i++;
		while (input[i] != '\0' && !ft_isspace(input[i]))
			i++;
		number_args++;
	}
	if (VERBOSE == 1)
		printf("set_input_pointers counted %i arguments\n", number_args);
	return (number_args);
}

/*Creates an array with pointers pointing to each word. Array is terminated
by a NULL pointer.*/
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
		//replacement of spaces by null bytes
		// while (input[i] == ' ')
		// 	input[i++] = '\0';
		while (input[i] == ' ')
			i++;
		if (input[i] == '\0')
			break ;
		args[i_args] = input + i;
		if (VERBOSE == 1)
			printf("set_input_pointers: setting pointer %i to %s\n", i_args, args[i_args]);
		i_args++;
		while (input[i] != ' ' && input[i] != '\0')
			i++;
	}
	args[i_args] = NULL;
	if (VERBOSE == 1)
		printf("set_input_pointers: setting pointer %i to %s\n", i_args, args[i_args]);
	return (args);
}
