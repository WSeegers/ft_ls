/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_long.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 09:11:53 by wseegers          #+#    #+#             */
/*   Updated: 2018/08/06 16:30:13 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "f_memory.h"

int			prepare_print(t_list *flist, t_col_width colw)
{
	int				i;
	int				block_total;
	t_stat			stats;
	struct passwd	*pwd;
	struct group	*grp;

	i = -1;
	block_total = 0;
	while (++i < flist->size)
	{
		stats = FLIST_GET(flist, i)->stats;
		pwd = getpwuid(stats.st_uid);
		grp = getgrgid(pwd->pw_gid);
		block_total += stats.st_blocks;
		colw[0] = MAX(colw[0], stats.st_nlink);
		colw[1] = MAX(colw[1], f_strlen(pwd->pw_name));
		colw[2] = MAX(colw[2], f_strlen(grp->gr_name));
		colw[3] = MAX(colw[3], stats.st_size);
	}
	colw[0] = count_digits(colw[0]);
	colw[3] = count_digits(colw[3]);
	return (block_total);
}

static void	print_mode(mode_t mode)
{
	int i;

	i = 0;
	i += (S_ISDIR(mode)) ? f_printf("d") : 0;
	i += (S_ISLNK(mode)) ? f_printf("l") : 0;
	(!i) && f_printf("-");
	(S_IRUSR & mode) ? f_printf("r") : f_printf("-");
	(S_IWUSR & mode) ? f_printf("w") : f_printf("-");
	(S_IXUSR & mode) ? f_printf("x") : f_printf("-");
	(S_IRGRP & mode) ? f_printf("r") : f_printf("-");
	(S_IWGRP & mode) ? f_printf("w") : f_printf("-");
	(S_IXGRP & mode) ? f_printf("x") : f_printf("-");
	(S_IROTH & mode) ? f_printf("r") : f_printf("-");
	(S_IWOTH & mode) ? f_printf("w") : f_printf("-");
	(S_IXOTH & mode) ? f_printf("x ") : f_printf("- ");
}

void		print_time(t_stat s)
{
	struct tm		*tm_;
	struct timespec	ts;

	ts = (g_flags & FLAG_ACCESS) ? s.st_atimespec : s.st_mtimespec;
	tm_ = localtime(&ts.tv_sec);
	f_printf("%2d %s %.2d:%.2d ", tm_->tm_mday,
		g_months[tm_->tm_mon],
		tm_->tm_hour, tm_->tm_min);
}

void		print_link(t_list *flist, t_list *plist, t_file_info *fi,
																ssize_t len)
{
	char buf[len + 1];

	buf[len] = '\0';
	s_list_append(plist, fi->file_name);
	readlink(get_path(plist), buf, len);
	f_printf(" -> %s", buf);
	s_list_pop(plist, -1);
}

void		print_long(t_list *flist, t_list *plist)
{
	t_file_info		*fi;
	int				i;
	struct passwd	*pwd;
	struct group	*grp;
	t_col_width		colw;

	i = -1;
	f_bzero(colw, sizeof(t_col_width));
	f_printf("total %d\n", prepare_print(flist, colw));
	while (++i < flist->size)
	{
		fi = FLIST_GET(flist, i);
		pwd = getpwuid(fi->stats.st_uid);
		grp = getgrgid(pwd->pw_gid);
		print_mode(fi->stats.st_mode);
		f_printf("%*d %*s  %*s ", colw[0], fi->stats.st_nlink,
			colw[1], pwd->pw_name, colw[1], grp->gr_name);
		f_printf("%*d ", colw[3], fi->stats.st_size);
		print_time(fi->stats);
		f_printf("%s", fi->file_name);
		if (S_ISLNK(fi->stats.st_mode))
			print_link(flist, plist, fi, fi->stats.st_size);
		f_printf("\n");
	}
}
