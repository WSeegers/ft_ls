/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/03 03:48:05 by wseegers          #+#    #+#             */
/*   Updated: 2018/08/06 10:29:04 by wseegers         ###   ########.fr       */
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

void		print_simple(t_list *flist, t_list *plist)
{
	t_file_info	*fi;
	int			i;

	(void)plist;
	i = -1;
	while (++i < flist->size)
	{
		fi = FLIST_GET(flist, i);
		f_printf("%s\n", fi->file_name);
	}
}

static int	get_max_len(t_list *flist, t_file_info *fi)
{
	int i;
	int	max_len;

	i = -1;
	max_len = 0;
	while (++i < flist->size)
	{
		fi = FLIST_GET(flist, i);
		max_len = MAX(max_len, f_strlen(fi->file_name) + 1);
	}
	return (max_len);
}

void		print_simple_v2(t_list *flist, t_list *plist)
{
	t_file_info	*fi;
	int			i;
	int			j;
	int			max_len;
	int			rows;

	(void)plist;
	max_len = get_max_len(flist, fi);
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
