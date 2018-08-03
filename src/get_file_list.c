/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/03 06:11:19 by wseegers          #+#    #+#             */
/*   Updated: 2018/08/03 06:12:58 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	get_file_list(t_list *flist, DIR *dir, int flag)
{
	t_dirent	de;

	while ((de = readdir(dir)) != NULL)
	{
		if (de->d_name[0] != '.')
			s_list_append(flist, de);
		else if (flag & FLAG_ALL)
			s_list_append(flist, de);
	}
	if (flag & FLAG_TIME)
	{
		if (flag & FLAG_REV)
			s_list_mergesort(flist, rtsort);
		else
			s_list_mergesort(flist, rtsort);
	}
	else if (flag & FLAG_REV)
		s_list_mergesort(flist, rsort);
	else
		s_list_mergesort(flist, sort);
}