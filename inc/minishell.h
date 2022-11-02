/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:18:50 by rbetz             #+#    #+#             */
/*   Updated: 2022/11/02 16:04:31 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h> // malloc, free, exit
# include <unistd.h> // close, read, write, dup2, access, fork, pipe, execve
# include <fcntl.h> // open
# include <sys/wait.h> // wait, waitpid
# include <stdio.h> // fprintf(int fd, char *stringset, ...) perror
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>

# include "libft.h"
# include "builtins.h"
# include "environment.h"
# include "errorhandling.h"
# include "history.h"
# include "parsing.h"
# include "pipes.h"
# include "redirects.h"
# include "signal.h"
# include "execute.h"
# include "filedescriptors.h"
# include "utils.h"
# include "structs.h"


#endif