/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:03:07 by pnolte            #+#    #+#             */
/*   Updated: 2022/11/07 14:07:08 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_prompt(t_data *data)
{
	data->prompt.name = "minishell";
	data->prompt.seperator = "@";
	data->prompt.dir = "src";
	data->prompt.endl = "$:";
	data->prompt.prompt = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	t_var	*var;
	//TEST
	t_data	*data;
	data = ft_calloc(1, sizeof(t_data));
	init_prompt(data);
	data->prompt.prompt=multijoin(false, 4, data->prompt.name, data->prompt.seperator, data->prompt.dir, data->prompt.endl);
	// ft_printf(">%s<\n", data->prompt);
	while (1)
	{
	data->input=readline(data->prompt.prompt);
	if (data->input != NULL && *data->input != '\0' && *(data->input) != '\n')
		add_history(data->input);
	ft_printf(">%s<\n", data->input);
	}
	free(data->prompt.prompt);
	free(data);
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
