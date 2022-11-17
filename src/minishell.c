/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:03:07 by pnolte            #+#    #+#             */
/*   Updated: 2022/11/17 17:39:05 by fkernbac         ###   ########.fr       */
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

int	main(int argc, char **argv, char **envp)
{
	t_prompt	*prompt;
	char		*input;
	t_cmd		*cmd_head;
	t_env		*env;
	// t_exec		*tmpexe;
	(void)argc;
	(void)argv;
	prompt = init_prompt();
	input = NULL;
	cmd_head = NULL;
	env = extract_env(envp);
	while (1)
	{
		input = readline(prompt->prompt);
		if (input != NULL && input[0] != '\0' && input[0] != '\n')
			add_history(input);
		printf(">%s<\n", input);
		//working on this:
		cmd_head = str_to_lst(input, env);
		// tmpexe =
		int ret;
		ret = execve(cmd_head->argv[0], cmd_head->argv, envp);
		//Fehler liegt hier im environment!!, uebergebe jetzt das originale, muss morgen schauen warum es mit unserem nicht geht

		
		printf("EXEC_RET:%d\n", ret);
		// executor(tmpexe, create_envp_from_env(env));
		input = ft_free(input);
		free_cmds(cmd_head);
	}
	free_multiple(1, prompt->prompt, prompt);
	return (0);
}
