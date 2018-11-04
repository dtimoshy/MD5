/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimoshy <dtimoshy@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 16:44:42 by dtimoshy          #+#    #+#             */
/*   Updated: 2018/11/04 19:13:38 by dtimoshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

static void			parse_fd_nul(t_ssl_md5 *handler)
{
	t_content		*content;

	if (handler->p > 1)
	{
		content = (t_content *)malloc(sizeof(t_content));
		content->content = (unsigned char *)ft_strdup("");
		content->cont_len = 0;
		handler->f(content);
		ft_printf("\n");
		free(content);
		return ;
	}
	content = (t_content *)malloc(sizeof(t_content));
	ft_read_from_fd(0, content, BUF_READ);
	if (handler->p)
		ft_printf("%s", content->content);
	handler->f(content);
	ft_printf("\n");
	free(content);
}

static void			parse_fd(t_ssl_md5 *handler, int fd, char *name)
{
	t_content		*content;
	struct stat		st;

	if (!handler->r && !handler->q)
		ft_printf("%s (%s) = ", ft_strto(handler->name, 1), name);
	content = (t_content *)malloc(sizeof(t_content));
	stat(name, &st);
	ft_read_from_fd(fd, content, (size_t)st.st_size);
	handler->f(content);
	if (handler->r && !handler->q)
		ft_printf(" %s", name);
	ft_printf("\n");
	free(content);
}

static void			parce_flags(t_ssl_md5 *handler, char **argv,
					int argc, int *i)
{
	int k;

	k = 0;
	while (++k && argv[*i][k])
	{
		if (!(ft_strchr("pqrs", argv[*i][k])))
			ft_flag_error(handler, argv[*i][k], 0);
		if (argv[*i][k] == 'q')
			handler->q = 1;
		if (argv[*i][k] == 'r')
			handler->r = 1;
		if (argv[*i][k] == 'p' && ++handler->p)
			parse_fd_nul(handler);
		if (argv[*i][k] == 's')
		{
			handler->stdin_write = 1;
			if (*i == argc - 1 && !argv[*i][k + 1])
				ft_flag_error(handler, argv[*i][k], 1);
			else
				parse_s_string(handler, argv, i, &k);
		}
	}
}

void				parse_arguments(t_ssl_md5 *handler, char **argv, int argc)
{
	int i;
	int fd;

	i = 0;
	while (++i < argc)
		if (argv[i][0] == '-' && argv[i][1])
			parce_flags(handler, argv, argc, &i);
		else
		{
			while (i < argc && ++handler->stdin_write)
			{
				fd = open(argv[i], O_RDONLY);
				if (fd < 0 || read(fd, 0, 0) < 0)
					ft_error_opening(handler->name, argv[i], strerror(errno));
				else
					parse_fd(handler, fd, argv[i]);
				i++;
				close(fd);
			}
			break ;
		}
	if (handler->stdin_write == 0 && (handler->p == 0 || handler->q
		|| handler->r))
		parse_fd_nul(handler);
}
