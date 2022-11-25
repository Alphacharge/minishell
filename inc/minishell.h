/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:18:50 by rbetz             #+#    #+#             */
/*   Updated: 2022/11/25 15:19:41 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define VERBOSE	0

# define BLTIN		0
# define EXEC		1
# define REDIR		2
# define PIPE		3
# define LIST		4
# define BACK		5

# define RED	"\x01\033[1;31m\x02"
# define GREEN	"\x01\033[1;32m\x02"
# define YELL	"\x01\033[1;33m\x02"
# define BLUE	"\x01\033[1;34m\x02"
# define WHITE	"\x01\033[0m\x02"

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
# include "execute.h"
# include "errorhandling.h"
# include "memory.h"
# include "history.h"
# include "parsing.h"
# include "pipes.h"
# include "redirects.h"
# include "signals.h"
# include "execute.h"
// # include "filedescriptors.h"
# include "utils.h"
# include "structs.h"

#endif
