/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 09:25:39 by rbetz             #+#    #+#             */
/*   Updated: 2022/12/23 17:48:40 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdbool.h>
# include "libft.h"

char	*combine_pathprog(char *path, char *prog);
char	*multijoin(bool tofrn, int n, ...);
void	free_multiple(int n, ...);
void	*free_ptr_array(void **array);
void	*ft_free(void *pointer);
char	*skip_space(char *ptr);
char	*skip_word(char *s);
char	*skip_argument(char *s);
int		is_word(char c);
int		is_token(char c);
int		ft_strcmp(char *s1, char *s2);
int		arraycount(char **array);
char	*get_word(char	*s);
char	*ft_last_word(const char *str, char c, int rev);
char	*multijoin_array(bool tofr, char **array);
int		is_valid_var(char *var);

#endif
