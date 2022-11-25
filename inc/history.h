/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 09:37:01 by rbetz             #+#    #+#             */
/*   Updated: 2022/11/25 15:08:46 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

# include "libft.h"
# include "errorhandling.h"
# include <fcntl.h>
# include <readline/history.h>

# define FILENAME "./.ms_history"
# define ALTFILENAME "~/.ms_history"

typedef struct s_hist
{
	int				fd;
}					t_hist;

t_hist	init_history(void);

#endif
