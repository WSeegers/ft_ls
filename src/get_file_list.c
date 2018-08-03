/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/03 06:11:19 by wseegers          #+#    #+#             */
/*   Updated: 2018/08/03 12:11:21 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	get_file_list(t_list *flist, t_list *plist, int flag)
{
	DIR			*dir;
	t_dirent	de;
	t_file_info	*fi;
	bool		add;

	dir = opendir(get_path(plist));
	while ((de = readdir(dir)) != NULL)
	{
		if (de->d_name[0] != '.' || flag & FLAG_ALL)
		{
			fi = malloc(sizeof(*fi));
			fi->file_name = f_strdup(de->d_name);
			s_list_append(plist, f_strdup(de->d_name));
			lstat(get_path(plist), &(fi->stats));
			s_list_append(flist, fi);
			free(s_list_pop(plist, -1));
		}
	}
	closedir(dir);
	// Extract to the sort file
	if (flag & FLAG_TIME)
	{
		if (flag & FLAG_REV)
			s_list_mergesort(flist, rtsort);
		else
			s_list_mergesort(flist, tsort);
	}
	else if (flag & FLAG_REV)
		s_list_mergesort(flist, rsort);
	else
		s_list_mergesort(flist, sort);
}