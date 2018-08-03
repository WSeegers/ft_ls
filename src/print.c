/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/03 03:48:05 by wseegers          #+#    #+#             */
/*   Updated: 2018/08/03 12:08:42 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "f_memory.h"

static int	get_term_width(void)
{
	struct winsize w;

	ioctl(0, TIOCGWINSZ, &w);
	return (w.ws_col);
}

void	print_simple(t_list *flist)
{
	t_file_info	*fi;
	int			i;

	i = -1;
	while (++i < flist->size)
	{
		fi = FLIST_GET(flist, i);
		f_printf("%s\n", fi->file_name);
	}
}

void	print_simple_v2(t_list *flist)
{
	t_file_info	*fi;
	int			i;
	int 		j;
	int			max_len;
	int 		rows;

	max_len = 0;
	i = -1;
	while (++i < flist->size)
	{
		fi = FLIST_GET(flist, i);
		max_len = MAX(max_len, f_strlen(fi->file_name) + 1);
	}
	rows = flist->size / (get_term_width() / max_len) + 1;
	j = -1;
	while (++j < rows && (i = -1))
	{
		while (1)
		{
			if (++i * rows + j >= flist->size)
				break;
			fi = FLIST_GET(flist, i * rows + j);
			f_printf("%-*s", max_len, fi->file_name);
		}
		f_printf("\n");
	}
}

unsigned int	count_digits(unsigned int n)
{
	unsigned int i;

	i = 1;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

int		prepare_print(t_list *flist, t_col_width colw)
{
	int 			i;
	int				block_total;
	t_stat			stats;

	i = -1;
	block_total = 0;
	while (++i < flist->size)
	{
		stats = FLIST_GET(flist, i)->stats;
		block_total += stats.st_blocks;
		colw[0] = MAX(colw[0], stats.st_nlink);
		colw[1] = MAX(colw[1], stats.st_size);
	}
	colw[0] = count_digits(colw[0]);
	colw[1] = count_digits(colw[1]);
	return (block_total);
}

void static	print_mode(mode_t mode)
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
	(S_IXOTH & mode) ? f_printf("x") : f_printf("-");
	f_printf(" ");
}

void	print_date(struct timespec last_mod)
{
	struct tm *ts;

	ts = localtime(&last_mod.tv_sec);
	f_printf("%2d %s %.2d:%.2d ", ts->tm_mday,
		g_months[ts->tm_mon], 
		ts->tm_hour, ts->tm_min);
}

void	print_long(t_list *flist)
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
		f_printf("%*d %s  %s ", colw[0], fi->stats.st_nlink, pwd->pw_name, grp->gr_name);
		f_printf("%*d ", colw[1], fi->stats.st_size);
		print_date(fi->stats.st_mtimespec);
		f_printf("%s\n", fi->file_name);
	}
}