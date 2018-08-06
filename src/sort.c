/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/03 06:14:00 by wseegers          #+#    #+#             */
/*   Updated: 2018/08/06 15:56:57 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		tsort(void *p1, void *p2)
{
	t_stat				s1;
	t_stat				s2;
	struct timespec		t1;
	struct timespec		t2;
	time_t				t;

	s1 = ((t_file_info*)p1)->stats;
	s2 = ((t_file_info*)p2)->stats;
	t1 = (g_flags & FLAG_ACCESS) ? s1.st_atimespec : s1.st_mtimespec;
	t2 = (g_flags & FLAG_ACCESS) ? s2.st_atimespec : s2.st_mtimespec;
	if (!(t = t1.tv_sec - t2.tv_sec))
		return (sort(p1, p2));
	else
		return (t);
}

int		rtsort(void *p1, void *p2)
{
	t_stat				s1;
	t_stat				s2;
	struct timespec		t1;
	struct timespec		t2;
	time_t				t;

	s1 = ((t_file_info*)p1)->stats;
	s2 = ((t_file_info*)p2)->stats;
	t1 = (g_flags & FLAG_ACCESS) ? s1.st_atimespec : s1.st_mtimespec;
	t2 = (g_flags & FLAG_ACCESS) ? s2.st_atimespec : s2.st_mtimespec;
	if (!(t = t2.tv_sec - t1.tv_sec))
		return (t2.tv_nsec - t1.tv_nsec);
	else
		return (t);
}

int		sort(void *p1, void *p2)
{
	t_file_info	*fi1;
	t_file_info	*fi2;

	fi1 = (t_file_info*)p1;
	fi2 = (t_file_info*)p2;
	return (-f_strcmp(fi1->file_name, fi2->file_name));
}

int		rsort(void *p1, void *p2)
{
	t_file_info	*fi1;
	t_file_info	*fi2;

	fi1 = (t_file_info*)p1;
	fi2 = (t_file_info*)p2;
	return (f_strcmp(fi1->file_name, fi2->file_name));
}
