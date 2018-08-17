/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_str.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/03 03:50:53 by wseegers          #+#    #+#             */
/*   Updated: 2018/08/17 10:14:28 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char		*void_to_str(void *str)
{
	return ((char*)str);
}

char		*get_path(t_list *plist)
{
	return (s_list_tostr(plist, '/', void_to_str));
}
