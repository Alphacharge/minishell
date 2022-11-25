/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:03:07 by rbetz             #+#    #+#             */
/*   Updated: 2022/11/25 15:48:30 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_cmds(t_cmd *lst)
{
	t_redir	*redir;
	int		i;

	i = 0;
	printf("\n-------------------\n");
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
			printf("> %s ", redir->file);
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
	prompt->prompt = multijoin(false, 8, GREEN, prompt->name, RED, prompt->seperator, YELL, prompt->dir, prompt->endl, WHITE);
	return (prompt);
}

int	main(int argc, char **argv, char **envp)
{
	t_prompt	*prompt;
	char		*input;
	t_cmd		*cmd_head;
	t_env		*env;
	t_hist		hist;
	int			ret;

	(void)argc;
	(void)argv;
	set_signals();
	env = extract_env(envp);
	prompt = init_prompt();
	hist = init_history();
	input = NULL;
	cmd_head = NULL;
	ret = -1;
	while (ret < 0)
	{
		input = readline(prompt->prompt);
		// printf(">%s<\n", envp[1]);
		if (input != NULL && input[0] != '\0' && input[0] != '\n')
		{
			add_history(input);
			ft_putendl_fd(input, hist.fd);
		}
		if (input == NULL)
		{
			//exit still after linebreak
			write(1, "exit\n", 5);
			ret = 0;
			break ;
		}
		cmd_head = str_to_lst(input, env);
		if (VERBOSE == 1)
			print_cmds(cmd_head);
		ret = execute_list(cmd_head, &env);
		free_multiple(1, &input);
		free_cmds(cmd_head);
	}
	close(hist.fd);
	rl_clear_history();
	// exit(0);
	delete_env(env);
	free_multiple(2, prompt->prompt, prompt);
	// system("leaks minishell");
	return (ret);
}
