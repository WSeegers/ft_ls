/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/03 06:11:19 by wseegers          #+#    #+#             */
/*   Updated: 2018/08/06 16:29:03 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static bool	is_defult(const char *name)
{
	if (name[0] == '.')
		if (name[1] == '\0' || name[1] == '.')
			return (true);
	return (false);
}

static void	sort_files(t_list *flist)
{
	if (g_flags & FLAG_TIME)
	{
		if (g_flags & FLAG_REV)
			s_list_mergesort(flist, rtsort);
		else
			s_list_mergesort(flist, tsort);
	}
	else if (g_flags & FLAG_REV)
		s_list_mergesort(flist, rsort);
	else
		s_list_mergesort(flist, sort);
}

static void	validate_files(t_list *flist, t_list *plist, DIR *dir)
{
	t_dirent	de;
	t_file_info	*fi;
	int			(*stat_func)(const char*, struct stat*);

	stat_func = (g_flags & FLAG_LINK) ? stat : lstat;
	while ((de = readdir(dir)) != NULL)
	{
		if (de->d_name[0] != '.' || g_flags & FLAG_ALL || g_flags & FLAG_AALL)
		{
			if (g_flags & FLAG_AALL && is_defult(de->d_name))
				continue ;
			fi = malloc(sizeof(*fi));
			fi->file_name = f_strdup(de->d_name);
			s_list_append(plist, f_strdup(de->d_name));
			stat_func(get_path(plist), &(fi->stats));
			s_list_append(flist, fi);
			free(s_list_pop(plist, -1));
		}
	}
}

int			get_file_list(t_list *flist, t_list *plist)
{
	DIR			*dir;
	t_dirent	de;

	if (!(dir = opendir(get_path(plist))))
	{
		f_printf("ls: %s: %s\n", s_list_get(plist, plist->size - 1),
			strerror(errno));
		return (-1);
	}
	validate_files(flist, plist, dir);
	closedir(dir);
	if (!(g_flags & FLAG_NSORT))
		sort_files(flist);
	return (0);
}
