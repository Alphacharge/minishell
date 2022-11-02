/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:03:07 by pnolte            #+#    #+#             */
/*   Updated: 2022/11/02 16:31:24 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_prompt(t_prompt prompt)
{
	prompt.name = "minishell";
	prompt.seperator = '#';
	prompt.dir = "src";
	prompt.endl = '$';
}

int	main(int argc, char **argv, char **envp)
{
	t_var	*var;
	//TEST
	t_data	data;
	init_prompt(data.prompt);
	ft_printf(">%s<\n", multijoin(false, data.prompt.name, data.prompt.seperator, data.prompt.dir, data.prompt.endl));
	exit(0);
	while (1)
	{
	data.input=readline(multijoin(false, data.prompt.name, data.prompt.seperator, data.prompt.dir, data.prompt.endl));
	if (data.input != NULL && *data.input != '\0' && *(data.input) != '\n')
		add_history(data.input);
	ft_printf(">%s<\n", data.input);
	}
	//END TEST
	var = ft_calloc(1, sizeof(t_var));
	if (var == NULL)
		ft_error(var, 1);
	if (envp == NULL)
		ft_error(var, 5);
	parse_args(var, argc, argv, envp);
	parse_progs(var, argv, envp);
	waitpid(-1, NULL, 0);
	ft_error(var, 0);
}
