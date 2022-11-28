/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:03:07 by rbetz             #+#    #+#             */
/*   Updated: 2022/11/28 11:27:20 by rbetz            ###   ########.fr       */
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

static t_prompt	*init_prompt(t_env *env)
{
	t_prompt	*prompt;

	prompt = ft_calloc(1, sizeof(t_prompt));
	prompt->name = "minishell";
	prompt->seperator = "@";
	prompt->dir = ft_last_word(get_env_var(env, "PWD"), '/', 0);
	prompt->endl = "$:";
	prompt->prompt = multijoin(false, 8, GREEN, prompt->name, RED, prompt->seperator, YELL, prompt->dir, prompt->endl, WHITE);
	return (prompt);
}
static t_data	*initialize_minishell(char **envp)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	if (data == NULL)
		return (NULL);
	data->env = extract_env(envp);
	data->prompt = init_prompt(data->env);
	data->hist = init_history();
	set_signals();
	return (data);
}

int	main(int argc, char **argv, char **envp)
{
	t_data		*data;
	char		*input;
	t_cmd		*cmd_head;
	int			ret;

	(void)argc;
	(void)argv;
	data = initialize_minishell(envp);
	input = NULL;
	cmd_head = NULL;
	ret = -1;
	while (ret < 0)
	{
		input = readline(data->prompt->prompt);
		// printf(">%s<\n", envp[1]);
		if (input != NULL && input[0] != '\0' && input[0] != '\n')
		{
			add_history(input);
			ft_putendl_fd(input, data->hist.fd);
		}
		if (input == NULL)
		{
			//exit still after linebreak
			write(1, "exit\n", 5);
			ret = 0;
			break ;
		}
		cmd_head = str_to_lst(input, data->env);
		if (VERBOSE == 1)
			print_cmds(cmd_head);
		ret = execute_list(cmd_head, data);
		free_multiple(1, &input);
		free_cmds(cmd_head);
	}
	ms_cleanup(data);
	// system("leaks minishell");
	return (ret);
}
