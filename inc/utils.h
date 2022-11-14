/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 09:25:39 by rbetz             #+#    #+#             */
/*   Updated: 2022/11/14 12:38:56 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdbool.h>

// # include ".h"
// # include "structs.h"
# include "libft.h"

char	*first_word(const char *str, char c, int rev);
char	*combine_pathprog(char *path, char *prog);
char	*multijoin(bool tofrn, int n, ...);
void	free_multiple(int n, ...);
void	*ft_free(void *pointer);

#endif
