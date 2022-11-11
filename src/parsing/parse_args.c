/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 09:27:08 by rbetz             #+#    #+#             */
/*   Updated: 2022/11/07 21:15:16 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "parsing.h"

static void	init_var(t_var *var, int argc)
{
	var->calls = argc - 3 - var->here;
	var->args = ft_calloc(var->calls + 1, sizeof(char **));
	var->exec = NULL;
	var->index_fd = 0;
	var->path = NULL;
}

static void	find_limiter(t_var *var, char **argv)
{
	char	*limiter;
	char	*tmp;
	int		len;

	limiter = ft_strjoin(argv[2], "\n");
	pipe(var->here_fd);
	while (1)
	{
		tmp = get_next_line(0);
		len = ft_strlen(tmp);
		write(var->here_fd[1], tmp, len);
		if (ft_strlen(limiter) > len)
			len = ft_strlen(limiter);
		if (ft_strncmp(tmp, limiter, len) == 0)
		{
			free(tmp);
			break ;
		}
		free(tmp);
	}
	free(limiter);
	close(var->here_fd[1]);
}

void	parse_args(t_var *var, int argc, char **argv, char **envp)
{
	if (argc < 5)
		ft_error(var);
	if (argc > 5 && ft_strncmp(argv[1], "here_doc", 8) == 0)
		var->here = 1;
	else
		var->here = 0;
	init_var(var, argc);
	get_env(var, envp);
	if (var->here == 0)
		check_infile(var, argv);
	else
		find_limiter(var, argv);
	check_outfile(var, argc, argv);
}
