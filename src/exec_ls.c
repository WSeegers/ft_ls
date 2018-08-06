/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ls.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/03 06:15:32 by wseegers          #+#    #+#             */
/*   Updated: 2018/08/06 13:41:08 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ls_rec(t_list *flist, t_list *plist,
												void (*print)(t_list*, t_list*))
{
	t_file_info	*fi;
	struct stat	stats;
	const char	*path;

	while (flist->size)
	{
		fi = (t_file_info*)s_list_pop(flist, 0);
		s_list_append(plist, f_strdup(fi->file_name));
		path = get_path(plist);
		lstat(path, &stats);
		if (S_ISDIR(stats.st_mode))
		{
			f_printf("\n%s\n", path);
			path = get_path(plist);
			exec_ls(path, print);
		}
		free(s_list_pop(plist, -1));
		free(fi->file_name);
		free(fi);
	}
}

void	exec_ls(const char *path, void (*print)(t_list*, t_list*))
{
	t_list			plist;
	t_list			flist;
	char			*temp;

	s_list_init(&plist, free);
	s_list_init(&flist, free);
	s_list_append(&plist, f_strdup(path));
	if (!get_file_list(&flist, &plist))
	{
		print(&flist, &plist);
		if (g_flags & FLAG_REC)
			ls_rec(&flist, &plist, print);
	}
	s_list_clear(&plist);
	s_list_clear(&flist);
}
