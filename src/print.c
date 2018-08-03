/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/03 03:48:05 by wseegers          #+#    #+#             */
/*   Updated: 2018/08/03 06:09:24 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	get_term_width(void)
{
	struct winsize w;

	ioctl(0, TIOCGWINSZ, &w);
	return (w.ws_col);
}

void	print_simple(t_list *flist)
{
	t_dirent	de;
	int			i;

	i = -1;
	while (++i < flist->size)
	{
		de = FLIST_GET(flist, i);
		f_printf("%s\n", de->d_name);
	}
}

void	print_simple_v2(t_list *flist)
{
	t_dirent	de;
	int			i;
	int 		j;
	int			file_per_line;
	int			max_len;
	int 		rows;

	max_len = 0;
	i = -1;
	while (++i < flist->size)
	{
		de = FLIST_GET(flist, i);
		max_len = MAX(max_len, de->d_namlen + 1);
	}
	file_per_line = (get_term_width() / max_len);
	rows = flist->size / (get_term_width() / max_len) + 1;
	j = -1;
	while (++j < rows && (i = -1))
	{
		while (1)
		{
			if (++i * rows + j >= flist->size)
				break;
			de = FLIST_GET(flist, i * rows + j);
			f_printf("%-*s", max_len, de->d_name);
		}
		f_printf("\n");
	}
}