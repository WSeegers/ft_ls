/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 19:54:47 by wseegers          #+#    #+#             */
/*   Updated: 2018/08/06 14:08:50 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <pwd.h>
# include <grp.h>
# include <stdbool.h>
# include <stdlib.h>
# include <limits.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <time.h>
# include <errno.h>
# include <string.h>
# include "f_math.h"
# include "f_print.h"
# include "s_list.h"
# include "f_cntl.h"
# include "f_string.h"

typedef struct dirent	*t_dirent;
typedef struct stat		t_stat;

typedef	struct			s_file_info
{
	char		*file_name;
	t_stat		stats;
}						t_file_info;

# define FLIST_GET(list, i)	((t_file_info*)s_list_get((list), (i)))

typedef int						t_flags;

t_flags							g_flags;

# define SHIFT(n)				(1 << n)
# define SET_FLAG(flags, opt)	(flags |= SHIFT(opt))
# define FLAGED(flags, flag)	((flags) & flag)

# define FLAGS "artlACR"

# define FLAG_ALL				(SHIFT(0))
# define FLAG_REV				(SHIFT(1))
# define FLAG_TIME				(SHIFT(2))
# define FLAG_LONG				(SHIFT(3))
# define FLAG_AALL				(SHIFT(4))
# define FLAG_COL				(SHIFT(5))
# define FLAG_REC				(SHIFT(6))

const char				*g_months[12];

typedef int				t_col_width[4];

void					print_simple(t_list *flist, t_list *plist);
void					print_col(t_list *flist, t_list *plist);
void					print_long(t_list *flist, t_list *plist);

void					ls_rec(t_list *flist, t_list *plist,
							void (*print)(t_list*, t_list*));
void					exec_ls(const char *path,
							void (*print)(t_list*, t_list*));
int						get_file_list(t_list *flist, t_list *plist);

int						tsort(void *p1, void *p2);
int						rtsort(void *p1, void *p2);
int						sort(void *p1, void *p2);
int						rsort(void *p1, void *p2);

char					*void_to_str(void *str);
const char				*get_path(t_list *plist);

unsigned int			count_digits(unsigned int n);

#endif
