/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:03:07 by pnolte            #+#    #+#             */
/*   Updated: 2022/11/13 18:51:44 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static t_prompt	*init_prompt(void)
// {
// 	t_prompt	*prompt;

// 	prompt = calloc(1, sizeof(t_prompt));
// 	prompt->name = "minishell";
// 	prompt->seperator = "@";
// 	prompt->dir = "src";
// 	prompt->endl = "$:";
// 	prompt->prompt = multijoin(false, 4, prompt->name, prompt->seperator, prompt->dir, prompt->endl);
// 	return (prompt);
// }

int	main()
{
	// t_var		*var;
	char	*prompt;
	char		*input;
	char		**args;
	t_cmd		*cmd_head;

	// prompt = init_prompt();
	prompt = "minishell: ";
	input = NULL;
	cmd_head = NULL;
	while (1)
	{
		input = readline(prompt);
		if (input != NULL && input[0] != '\0' && input[0] != '\n')
			add_history(input);
		printf(">%s<\n", input);
		args = set_input_pointers(input);
		cmd_head = create_list(args);
		if (execute(cmd_head) != 0)
			break ;
		input = ft_free(input);
		args = ft_free(args);
		free_cmds(cmd_head);
	}
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
