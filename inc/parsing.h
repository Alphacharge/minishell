/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 09:19:48 by rbetz             #+#    #+#             */
/*   Updated: 2022/10/28 09:59:33 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <minishell.h>

void	parse_progs(t_var *var, char **argv, char **envp);
void	parse_args(t_var *var, int argc, char **argv, char **envp);

#endif