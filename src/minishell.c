/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:03:07 by pnolte            #+#    #+#             */
/*   Updated: 2022/11/19 14:25:36 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_new = 0;

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
	int			ret;

	(void)argc;
	(void)argv;
	set_signals();
	prompt = init_prompt();
	input = NULL;
	cmd_head = NULL;
	env = extract_env(envp);
	ret = -1;
	while (ret < 0)
	{
		input = readline(prompt->prompt);
		// printf(">%s<\n", input);
		if (g_new == 1)
		{
			g_new = 0;
			continue ;
		}
		if (input != NULL && input[0] != '\0' && input[0] != '\n')
			add_history(input);
		if (input == NULL)
		{
			write(1,"\n", 1);
			ret = shell_exit(NULL);
			break ;
		}
		cmd_head = str_to_lst(input, env);
		ret = execute_list(cmd_head, env);
		input = ft_free(input);
		free_cmds(cmd_head);
	}
	free_multiple(2, prompt->prompt, prompt);
	system("leaks minishell");
	return (ret);
}
