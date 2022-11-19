/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:18:50 by rbetz             #+#    #+#             */
/*   Updated: 2022/11/19 13:05:07 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define VERBOSE	1

# define BLTIN		0
# define EXEC		1
# define REDIR		2
# define PIPE		3
# define LIST		4
# define BACK		5

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
