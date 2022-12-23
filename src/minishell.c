/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:03:07 by rbetz             #+#    #+#             */
/*   Updated: 2022/12/23 17:15:00 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_cmds(t_cmd *lst)
{
	t_param	*param;
	t_redir	*redir;
	int		i;

	i = 0;
	printf("\n-------------------\n");
	while (lst != NULL)
	{
		param = lst->param;
		redir = lst->redir;
		if (lst->name != NULL)
			printf("name: %s\n", lst->name);
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
		printf("argv: ");
		while (lst->argv != NULL && lst->argv[i] != NULL)
			printf("|%s| ", lst->argv[i++]);
		printf("\n");
		if (lst->next != NULL)
			printf("---pipe-->\n");
		i = 0;
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
	//this is not read from history yet
	data->exit_status = 0;
	set_env_var(data->env, "SHLVL", \
		ft_itoa(ft_atoi(get_env_var(data->env, "SHLVL")) + 1));
	return (data);
}

int	main(int argc, char **argv, char **envp)
{
	t_data		*data;
	int			ret;
	bool		c;

	c = false;
	data = initialize_minishell(envp);
	if (argc == 3 && ft_strcmp(argv[1], "-c") == 0 && argv[2] != NULL)
	{
		data->input = ft_strdup(argv[2]);
		c = true;
	}
	ret = -1;
	while (ret < 0)
	{
		set_rl_signals();
		if (data->input == NULL)
			data->input = readline(data->prompt->prompt);
		set_exec_signals();
		if (data->input != NULL && data->input[0] != '\0' && data->input[0] != '\n')
		{
			add_history(data->input);
			ft_putendl_fd(data->input, data->hist.fd);
		}
		if (data->input == NULL)
			data->input = ft_strdup("exit");
		data->cmd_head = parse(data->input, data);
		if (VERBOSE == 1)
			print_cmds(data->cmd_head);
		ret = execute_list(data->cmd_head, data);
		data->input = ft_free(data->input);
		free_cmds(data->cmd_head);
		if (c)
			break ;
	}
	ms_cleanup(data);
	// system("leaks minishell");
	return (ret);
}
