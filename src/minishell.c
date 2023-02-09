/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:03:07 by rbetz             #+#    #+#             */
/*   Updated: 2023/02/09 19:27:41 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Creates a dynamic prompt.*/
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

/*Initializes variables needed for minishell in data struct.*/
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
	data->exitstatus = 0;
	if (get_env_var(data->env, "SHLVL") != NULL)
		set_env_var(data->env, "SHLVL", \
			ft_itoa(ft_atoi(get_env_var(data->env, "SHLVL")) + 1));
	return (data);
}

/*Executes one command and returns.*/
static int	commandline_mode(char *input, t_data *data)
{
	int	exitstatus;

	set_exec_signals();
	data->cmd_head = parse(input, data);
	exitstatus = execute_list(data->cmd_head, data);
	if (exitstatus == -1)
		exitstatus = data->exitstatus;
	free_cmds(data->cmd_head);
	if (exitstatus < 0)
		return (exitstatus);
	return (exitstatus);
}

static void	termios_setup(void)
{
	struct termios	t;

	tcgetattr(0, &t);
	t.c_iflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &t);
}

/*Reads from input and returns only if exit command is entered.*/
static int	interactive_mode(t_data *data)
{
	int		ret;
	char	*input;

	ret = -1;
	data->hist = init_history();
	termios_setup();
	while (ret < 0)
	{
		set_rl_signals();
		input = readline(data->prompt->prompt);
		set_exec_signals();
		if (input != NULL && input[0] != '\0' && input[0] != '\n')
		{
			add_history(input);
			ft_putendl_fd(input, data->hist.fd);
		}
		if (input == NULL)
			input = ft_strdup("exit");
		data->cmd_head = parse(input, data);
		ret = execute_list(data->cmd_head, data);
		input = ft_free(input);
		free_cmds(data->cmd_head);
	}
	return (ret);
}

int	main(int argc, char **argv, char **envp)
{
	t_data		*data;
	int			ret;

	data = initialize_minishell(envp);
	if (argc == 3 && ft_strcmp(argv[1], "-c") == 0 && argv[2] != NULL)
		ret = commandline_mode(argv[2], data);
	else
		ret = interactive_mode(data);
	ms_cleanup(data);
	return (ret);
}
