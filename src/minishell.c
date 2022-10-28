/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:03:07 by pnolte            #+#    #+#             */
/*   Updated: 2022/10/28 13:13:18 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_var	*var;

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
