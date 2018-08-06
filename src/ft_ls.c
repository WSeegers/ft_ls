/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 19:54:15 by wseegers          #+#    #+#             */
/*   Updated: 2018/08/06 10:21:51 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			main(int ac, char *av[])
{
	t_flags		flag;

	flag = 0;
	exec_ls(flag, "./libwtcc/include", print_simple_v2);
	f_exit(0);
}
