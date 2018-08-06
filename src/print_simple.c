/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_simple.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/03 03:48:05 by wseegers          #+#    #+#             */
/*   Updated: 2018/08/06 15:11:52 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "f_memory.h"

void		print_simple(t_list *flist, t_list *plist)
{
	t_file_info	*fi;
	int			i;

	(void)plist;
	i = -1;
	while (++i < flist->size)
	{
		fi = FLIST_GET(flist, i);
		f_printf("%s\n", fi->file_name);
	}
}
