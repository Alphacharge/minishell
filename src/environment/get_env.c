/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 10:41:28 by rbetz             #+#    #+#             */
/*   Updated: 2022/11/14 12:31:43 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

// void	get_env(t_var *var, char **envp)
// {
// 	int		i;
// 	char	*line;
// 	char	**ptr;

// 	i = 0;
// 	line = envp[i];
// 	while (line != NULL)
// 	{
// 		if (!ft_strncmp(line, "PATH=", 5))
// 			var->path = ft_split(&line[5], ':');
// 		if (ft_strstr(line, "OLDPWD=") == NULL && \
// 			ft_strstr(line, "PWD=") != NULL)
// 			var->pwd = ft_substr(line, 4, ft_strlen(line));
// 		i++;
// 		line = envp[i];
// 	}
// 	if (var->path == NULL)
// 	{
// 		ptr = ft_calloc(1, sizeof(char **));
// 		line = ft_strdup(".");
// 		ptr[0] = line;
// 		var->path = ptr;
// 	}
// }
