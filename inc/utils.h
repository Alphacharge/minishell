/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 09:25:39 by rbetz             #+#    #+#             */
/*   Updated: 2022/11/18 16:26:10 by fkernbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdbool.h>

// # include ".h"
// # include "structs.h"
# include "libft.h"

char	*combine_pathprog(char *path, char *prog);
char	*multijoin(bool tofrn, int n, ...);
void	free_multiple(int n, ...);
void	*free_str_array(char **array);
void	*ft_free(void *pointer);
char	*skip_space(char *ptr);
char	*skip_word(char *s);
int		is_word(char c);
int		is_token(char c);

#endif
