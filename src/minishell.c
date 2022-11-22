/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:03:07 by rbetz             #+#    #+#             */
/*   Updated: 2022/11/22 19:04:44 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_cmds(t_cmd *lst)
{
	t_redir	*redir;
	int		i;

	i = 0;
	while (lst != NULL)
	{
		while (lst->argv[i] != NULL)
		{
			printf("%s ", lst->argv[i]);
			i++;
		}
		redir = lst->redir;
		while (redir != NULL)
		{
			printf("redir %s ", lst->redir->file);
			redir = redir->next;
		}
		if (lst->pipe != NULL)
			printf("| ");
		lst = lst->pipe;
	}
	printf("\n-------------------\n");
}

static t_prompt	*init_prompt(void)//t_env *env)
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
			write(1, "exit\n", 4);
			ret = 0;
			break ;
		}
		cmd_head = str_to_lst(input, env);
		if (VERBOSE == 1)
			print_cmds(cmd_head);
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
