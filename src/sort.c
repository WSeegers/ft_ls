/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/03 06:14:00 by wseegers          #+#    #+#             */
/*   Updated: 2018/08/03 06:14:09 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		tsort(void *p1, void *p2)
{
	return (1);
}

int		rtsort(void *p1, void *p2)
{
	return (-1);
}

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