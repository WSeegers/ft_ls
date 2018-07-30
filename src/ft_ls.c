/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 19:54:15 by wseegers          #+#    #+#             */
/*   Updated: 2018/07/30 23:47:21 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		sort(void *p1, void *p2)
{
	t_dirent	de1;
	t_dirent	de2;

	de1 = (t_dirent)p1;
	de2 = (t_dirent)p2;
	return (-f_strcmp(de1->d_name, de2->d_name));
}

int		rsort(void *p1, void *p2)
{
	t_dirent	de1;
	t_dirent	de2;

	de1 = (t_dirent)p1;
	de2 = (t_dirent)p2;
	return (f_strcmp(de1->d_name, de2->d_name));
}

void	get_flist(t_list *flist, DIR *dir, char sort, bool all)
{
	t_dirent	de;

	while ((de = readdir(dir)) != NULL)
	{
		if (de->d_name[0] != '.')
			s_list_append(flist, de);
		else if (all)
			s_list_append(flist, de);
	}
	if (sort == 'r')
		s_list_mergesort(flist, rsort);
	//else if (sort == 't')
		//s_list_mergesort(flist, tsort);
	else
		s_list_mergesort(flist, sort);
}

int	get_term_width(void)
{
	struct winsize w;

	ioctl(0, TIOCGWINSZ, &w);
	return (w.ws_col);
}

void	print_simple(t_list *flist)
{
	t_dirent	de;
	int			i;
	int			file_per_line;
	int			max_len;

	max_len = 0;
	while (++i < flist->size)
	{
		de = FLIST_GET(flist, i);
		max_len = MAX(max_len, de->d_namlen + 2);
	}
	file_per_line = get_term_width() / max_len;
	i = -1;
	while (++i < flist->size)
	{
		de = FLIST_GET(flist, i);
		f_printf("%-*s", max_len, de->d_name);
		if ((i && !(i % file_per_line)) || i + 1 == flist->size)
			f_printf("\n");
	}
}

int		main(int ac, char *av[])
{
	t_flags 	flag;
	DIR			*dir;
	t_dirent	de;
	t_list		flist;
	t_list		dlist;

	//if (flags(ac, av, &flags))
	//	f_eexit(0, "Invalid flags\n");
	s_list_init(&flist, free);
	dir = opendir(".");
	get_flist(&flist, dir, false, false);
	print_simple(&flist);
	print_long(&flist);

	int i = -1;

	closedir(dir);
	f_exit(0);
}