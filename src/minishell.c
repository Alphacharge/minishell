/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:03:07 by rbetz             #+#    #+#             */
/*   Updated: 2022/12/08 10:09:35 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_cmds(t_cmd *lst)
{
	t_param	*param;
	t_redir	*redir;

	printf("\n-------------------\n");
	while (lst != NULL)
	{
		if (lst->name != NULL)
			printf("name: %s\n", lst->name);
		param = lst->param;
		while (param != NULL)
		{
			printf("param: %s\n", param->arg);
			param = param->next;
		redir = lst->redir;
		}
		while (redir != NULL)
		{
			printf("redir: %s\n", redir->file);
			redir = redir->next;
		}
		if (lst->argv == NULL)
			printf("argv: NULL\n");
		else
			printf("argv: %s | %s\n", lst->argv[0], lst->argv[1]);
		if (lst->next != NULL)
			printf("pipe\n");
		lst = lst->next;
	}
	printf("-------------------\n");
}

static t_prompt	*init_prompt(t_env *env)
{
	t_prompt	*prompt;

	prompt = ft_calloc(1, sizeof(t_prompt));
	prompt->name = "minishell";
	prompt->seperator = "@";
	prompt->dir = ft_last_word(get_env_var(env, "PWD"), '/', 0);
	prompt->endl = "$:";
	prompt->prompt = multijoin(false, 8, GREEN, prompt->name, RED, \
			prompt->seperator, YELL, prompt->dir, prompt->endl, WHITE);
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
	data->cmd_head = NULL;
	data->input = NULL;
	set_signals();
	return (data);
}

int	main(int argc, char **argv, char **envp)
{
	t_data		*data;
	int			ret;

	(void)argc;
	(void)argv;
	data = initialize_minishell(envp);
	ret = -1;
	while (ret < 0)
	{
		data->input = readline(data->prompt->prompt);
		if (data->input != NULL && data->input[0] != '\0' && data->input[0] != '\n')
		{
			add_history(data->input);
			ft_putendl_fd(data->input, data->hist.fd);
		}
		if (data->input == NULL)
		{
			//exit still after linebreak
			write(2, "exit\n", 5);
			ret = 0;
			break ;
		}
		data->cmd_head = parse(data->input, data->env);
		if (VERBOSE == 10000000000)
			print_cmds(data->cmd_head);
		ret = execute_list(data->cmd_head, data->prompt);
		data->input = ft_free(data->input);
		free_cmds(data->cmd_head);
	}
	ms_cleanup(data);
	// system("leaks minishell");
	return (ret);
}
