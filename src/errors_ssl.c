/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_ssl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimoshy <dtimoshy@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 16:43:44 by dtimoshy          #+#    #+#             */
/*   Updated: 2018/10/29 16:43:51 by dtimoshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

extern	t_ssl_mode	g_mode_change[];

void				ft_mode_error(char *cmd)
{
	int i;

	ft_printf("ft_ssl: Error: '%s' is an invalid command.\n\n\
Standart commands:\n\n", cmd);
	ft_printf("Message Digest commands:\n");
	i = 0;
	while (g_mode_change[i].name)
	{
		ft_printf("%s\n", g_mode_change[i].name);
		i++;
	}
	ft_printf("\nCipher commands:\n\n");
	exit(1);
}

void				ft_flag_error(t_ssl_md5 *flags, char a, int mode)
{
	if (mode == 0)
		ft_printf("%s: illegal option -- %c\n", ft_strto(flags->name, 0), a);
	if (mode == 1)
		ft_printf("%s: option requires an argument -- s\n", flags->name);
	ft_printf("usage: %s [-pqr] [-s string] [files ...]\n", flags->name);
	ft_strdel(&flags->name);
	free(flags);
	exit(1);
}

void				ft_error_opening(char *name, char *func, char *error)
{
	ft_printf("%s: %s: %s\n", ft_strto(name, 0), func, error);
}
