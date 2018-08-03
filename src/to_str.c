/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_str.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/03 03:50:53 by wseegers          #+#    #+#             */
/*   Updated: 2018/08/03 04:43:00 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*de_to_str(void *dirent)
{
	t_dirent	de;

	de = (t_dirent)dirent;
	return (de->d_name);
}

char	*void_to_str(void *str)
{
	return ((char*)str);
}

const char *get_path(t_list *plist)
{
	return (s_list_tostr(plist, '/', void_to_str));
}