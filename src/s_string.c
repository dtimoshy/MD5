/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_string.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimoshy <dtimoshy@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 18:49:22 by dtimoshy          #+#    #+#             */
/*   Updated: 2018/11/04 18:49:24 by dtimoshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

static int		smth_after_s(t_ssl_md5 *handler, char *argv,
				int k, t_content *string)
{
	if (!handler->q && !handler->r)
		ft_printf("%s (\"%s\") = ", ft_strto(handler->name, 1), &argv[k + 1]);
	string->content = (unsigned char *)ft_strdup(&argv[k + 1]);
	string->cont_len = ft_strlen(&argv[k + 1]);
	handler->f(string);
	if (!handler->q && handler->r)
		ft_printf(" \"%s\"", &argv[k + 1]);
	k = k + (int)ft_strlen(&argv[k + 1]);
	return (k);
}

void			parse_s_string(t_ssl_md5 *handler, char **argv, int *i, int *k)
{
	t_content *string;

	string = (t_content *)malloc(sizeof(t_content));
	if (argv[*i][*k + 1])
		*k = smth_after_s(handler, argv[*i], *k, string);
	else
	{
		string->content = (unsigned char *)ft_strdup(argv[++(*i)]);
		string->cont_len = ft_strlen(argv[*i]);
		if (!handler->q && !handler->r)
			ft_printf("%s (\"%s\") = ", ft_strto(handler->name, 1), argv[*i]);
		handler->f(string);
		if (!handler->q && handler->r)
			ft_printf(" \"%s\"", argv[*i]);
		(*k) = (int)ft_strlen(argv[*i]) - 1;
	}
	free(string);
	ft_printf("\n");
}
