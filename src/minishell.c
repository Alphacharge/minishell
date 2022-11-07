/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:03:07 by pnolte            #+#    #+#             */
/*   Updated: 2022/11/07 21:58:02 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_prompt	*init_prompt(void)
{
	t_prompt	*prompt;

	prompt = calloc(1, sizeof(t_prompt));
	prompt->name = "minishell";
	prompt->seperator = "@";
	prompt->dir = "src";
	prompt->endl = "$:";
	prompt->prompt = multijoin(false, 4, prompt->name, prompt->seperator, prompt->dir, prompt->endl);
	return (prompt);
}

int	found_exit(char *input)
{
	if (input == NULL)
		return (0);
	if (input[0] != 'e' || input[1] != 'x' || input[2] != 'i' || input[3] != 't')
		return (0);
	if (input[4] != '\0' && input[4] != ' ')
		return (0);
	return (1);
}

int	main()
{
	// t_var		*var;
	t_prompt	*prompt;
	char		*input;

	prompt = init_prompt();
	input = NULL;
	while (found_exit(input) == 0)
	{
		input = readline(prompt->prompt);
		if (input != NULL && input[0] != '\0' && input[0] != '\n')
			add_history(input);
		printf(">%s<\n", input);
	}
	input = ft_free(input);
	prompt->prompt = ft_free(prompt->prompt);
	prompt = ft_free(prompt);
	//PIPEX START
	// var = ft_calloc(1, sizeof(t_var));
	// if (var == NULL)
	// 	ft_error(var);
	// if (envp == NULL)
	// 	ft_error(var);
	// parse_args(var, argc, argv, envp);
	// parse_progs(var, argv, envp);
	// waitpid(-1, NULL, 0);
	//PIPEX END
	return (0);
}
