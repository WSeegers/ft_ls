/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 19:54:15 by wseegers          #+#    #+#             */
/*   Updated: 2018/08/06 16:33:55 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_flags			g_flags = 0;

static void		*get_print_func(void)
{
	if (g_flags & FLAG_LONG)
		return (print_long);
	else if (isatty(1) || g_flags & FLAG_COL)
		return (print_col);
	else
		return (print_simple);
}

static int		get_opt(char c)
{
	int i;

	i = -1;
	while (FLAGS[++i])
		if (FLAGS[i] == c)
			return (i);
	return (-1);
}

static int		set_flags(int ac, char *av[])
{
	int				i;
	int				opt;
	char			*tok;

	i = 0;
	while (++i < ac)
	{
		if ((tok = av[i])[0] != '-')
			break ;
		while ((++tok)[0])
		{
			if ((opt = get_opt(tok[0])) < 0)
			{
				f_printf("ft_ls: illegal option -- %c\n", *tok);
				return (-1);
			}
			SET_FLAG((g_flags), opt);
		}
	}
	g_flags |= (g_flags & FLAG_NSORT) ? FLAG_ALL : 0;
	return (i);
}

int				main(int ac, char *av[])
{
	int		offset;
	void	(*print)(t_list*, t_list*);

	g_flags = 0;
	if ((offset = set_flags(ac, av)) < 0)
	{
		f_printf("usage: ls [-%s] [file ...]\n", FLAGS);
		f_exit(0);
	}
	print = get_print_func();
	if (offset >= ac)
		exec_ls(".", print);
	else if (ac - offset == 1)
		exec_ls(av[offset], print);
	else
		while (offset < ac)
		{
			if (av[offset][0] == '-' && offset++)
				continue ;
			f_printf("%s:\n", av[offset]);
			exec_ls(av[offset++], print);
			f_printf("\n");
		}
	f_exit(0);
}
