/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:03:07 by pnolte            #+#    #+#             */
/*   Updated: 2022/11/15 11:34:21 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_prompt	*prompt;
	char		*input;
	char		**args;
	t_cmd		*cmd_head;
	t_env		*env;
	// t_exec		*tmpexe;

	prompt = init_prompt();
	input = NULL;
	cmd_head = NULL;
	env = extract_env(envp);
	while (1)
	{
		input = readline(prompt);
		if (input != NULL && input[0] != '\0' && input[0] != '\n')
			add_history(input);
		printf(">%s<\n", input);
		args = set_input_pointers(input);
		cmd_head = create_list(args);
		// tmpexe = 
		// executor(tmpexe, create_envp_from_env(env));
		input = ft_free(input);
		args = ft_free(args);
		free_cmds(cmd_head);
	}
	free_multiple(1, prompt->prompt, prompt);
	return (0);
}
