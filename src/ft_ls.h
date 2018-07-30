/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 19:54:47 by wseegers          #+#    #+#             */
/*   Updated: 2018/07/30 23:39:10 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <dirent.h>
# include <sys/types.h>
# include <stdbool.h>
# include <stdlib.h>
# include <limits.h>
# include <termios.h>
# include <sys/ioctl.h>
# include "f_math.h"
# include "f_print.h"
# include "s_list.h"
# include "f_cntl.h"
# include "f_string.h"

typedef struct dirent	*t_dirent;

# define FLIST_GET(list, i)	((t_dirent)s_list_get((list), (i)))

typedef int		t_flags;

# define SHIFT(n)				(1 << n)
# define FLAGED(flags, flag)	((flags) & flag)

# define FLAG_LIST				(SHIFT(0))
# define FLAG_REC				(SHIFT(1))
# define FLAG_ALL				(SHIFT(2))
# define FLAG_REV				(SHIFT(3))
# define FLAG_TIME				(SHIFT(4))

#endif
