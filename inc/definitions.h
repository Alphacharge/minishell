/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   definitions.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humbi <humbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 16:18:50 by rbetz             #+#    #+#             */
/*   Updated: 2023/01/31 19:02:47 by humbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINITIONS_H
# define DEFINITIONS_H

//Debug
# define VERBOSE 0

//Redirections
# define FD_UNUSED INT32_MIN
# define STDIN 0
# define STDOUT 1
# define READ 0
# define WRITE 1

//Environment
# define RED	"\x01\033[1;31m\x02"
# define GREEN	"\x01\033[1;32m\x02"
# define YELL	"\x01\033[1;33m\x02"
# define BLUE	"\x01\033[1;34m\x02"
# define WHITE	"\x01\033[0m\x02"

//History
# define FILENAME "./.ms_history"
# define ALTFILENAME "~/.ms_history"

//Structs
# define INPUT		1
# define OUTPUT		2
# define HERE		3
# define APPEND		4

# define BLTIN		0
# define EXEC		1
# define REDIR		2
# define PIPE		3
# define LIST		4
# define BACK		5

#endif