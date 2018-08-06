/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_col.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 13:46:41 by wseegers          #+#    #+#             */
/*   Updated: 2018/08/06 14:39:12 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	get_term_width(void)
{
	struct winsize w;

	ioctl(0, TIOCGWINSZ, &w);
	return (w.ws_col);
}

static int	get_max_len(t_list *flist, t_file_info *fi)
{
	int i;
	int len;
	int	max_len;

	i = -1;
	max_len = 8;
	while (++i < flist->size)
	{
		fi = FLIST_GET(flist, i);
		max_len += ((len = f_strlen(fi->file_name)) >= max_len) ? 8 : 0;
	}
	return (max_len);
}

void		print_col(t_list *flist, t_list *plist)
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
				break ;
			fi = FLIST_GET(flist, i * rows + j);
			f_printf("%-*s", max_len, fi->file_name);
		}
		f_printf("\n");
	}
}
