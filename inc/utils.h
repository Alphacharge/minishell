/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 09:25:39 by rbetz             #+#    #+#             */
/*   Updated: 2022/11/02 16:32:39 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdbool.h>

# include "structs.h"
# include "libft.h"

char	*first_word(const char *str, char c, int rev);
char	*combine_pathprog(char *path, char *prog);
char	*multijoin(int n, bool tofr, ...);
#endif
