/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:03:07 by rbetz             #+#    #+#             */
/*   Updated: 2022/11/25 09:35:06 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_prompt	*init_prompt(void)//t_env *env)
{
	t_prompt	*prompt;

	prompt = calloc(1, sizeof(t_prompt));
	prompt->name = "\033[1;32mminishell";
	prompt->seperator = "\033[1;31m@";
	prompt->dir = "\033[1;33msrc";
	prompt->endl = "$:\033[0m";
	prompt->prompt = multijoin(false, 4, prompt->name, prompt->seperator, prompt->dir, prompt->endl);
	return (prompt);
}

int	main(int argc, char **argv, char **envp)
{
	t_prompt	*prompt;
	char		*input;
	t_cmd		*cmd_head;
	t_env		*env;
	int			ret;

	(void)argc;
	(void)argv;
	set_signals();
	env = extract_env(envp);
	prompt = init_prompt();
	input = NULL;
	cmd_head = NULL;
	ret = -1;
	while (ret < 0)
	{
		input = readline(prompt->prompt);
		// printf(">%s<\n", envp[1]);
		if (input != NULL && input[0] != '\0' && input[0] != '\n')
			add_history(input);
		if (input == NULL)
		{
			//exit still after linebreak
			write(1, "exit\n", 5);
			ret = 0;
			break ;
		}
		cmd_head = str_to_lst(input, env);
		ret = execute_list(cmd_head, env);
		input = ft_free(input);
		free_cmds(cmd_head);
	}
	delete_env(env);
	// rl_clear_history();
	free_multiple(2, prompt->prompt, prompt);
	// system("leaks minishell");
	return (ret);
}
