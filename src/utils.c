/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimoshy <dtimoshy@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 16:46:03 by dtimoshy          #+#    #+#             */
/*   Updated: 2018/11/04 19:00:42 by dtimoshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "ft_ssl_md5.h"
#include <sys/stat.h>

char		*ft_strto(char *string, int mode)
{
	size_t i;

	i = 0;
	while (i < ft_strlen(string))
	{
		if (mode == 0)
			string[i] = (char)ft_tolower(string[i]);
		if (mode == 1)
			string[i] = (char)ft_toupper(string[i]);
		i++;
	}
	return (string);
}

void		ft_read_from_fd(int fd, t_content *handler, size_t buf_size)
{
	void	*buf;
	void	*ret;
	ssize_t	bytes;

	buf = ft_memalloc(buf_size);
	handler->content = ft_memalloc(0);
	handler->cont_len = 0;
	while ((bytes = read(fd, buf, buf_size)) > 0)
	{
		if (!handler->content && !buf)
		{
			handler->content = NULL;
			break ;
		}
		ret = ft_memalloc(handler->cont_len + (size_t)bytes + 1);
		ft_memcpy(ret, handler->content, handler->cont_len);
		ft_memcpy(&ret[handler->cont_len], buf, (size_t)bytes);
		ft_memdel((void **)&handler->content);
		handler->content = ret;
		handler->cont_len += bytes;
		ft_bzero(buf, buf_size);
	}
	ft_memdel(&buf);
}
