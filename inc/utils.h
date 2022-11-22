/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 09:25:39 by rbetz             #+#    #+#             */
/*   Updated: 2022/11/22 14:55:52 by fkernbac         ###   ########.fr       */
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
void	*free_ptr_array(void **array);
void	*ft_free(void *pointer);
char	*skip_space(char *ptr);
char	*skip_word(char *s);
int		is_word(char c);
int		is_token(char c);
int		ft_strcmp(char *s1, char *s2);
int		arraycount(char **array);

#endif
