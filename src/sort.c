/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/03 06:14:00 by wseegers          #+#    #+#             */
/*   Updated: 2018/08/06 13:35:14 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		tsort(void *p1, void *p2)
{
	t_file_info	*fi1;
	t_file_info	*fi2;
	time_t		t1;
	time_t		t2;

	fi1 = (t_file_info*)p1;
	fi2 = (t_file_info*)p2;
	t1 = fi1->stats.st_mtimespec.tv_sec;
	t2 = fi2->stats.st_mtimespec.tv_sec;
	if (!(t1 - t2))
		return (fi1->stats.st_mtimespec.tv_nsec -
			fi2->stats.st_mtimespec.tv_nsec);
	else
		return (t1 - t2);
}

int		rtsort(void *p1, void *p2)
{
	t_file_info	*fi1;
	t_file_info	*fi2;
	time_t		t1;
	time_t		t2;

	fi1 = (t_file_info*)p1;
	fi2 = (t_file_info*)p2;
	t1 = fi1->stats.st_mtimespec.tv_sec;
	t2 = fi2->stats.st_mtimespec.tv_sec;
	if (!(t2 - t1))
		return (fi2->stats.st_mtimespec.tv_nsec -
			fi1->stats.st_mtimespec.tv_nsec);
	else
		return (t2 - t1);
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
