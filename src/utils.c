/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimoshy <dtimoshy@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 16:46:03 by dtimoshy          #+#    #+#             */
/*   Updated: 2018/10/29 16:46:04 by dtimoshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "ft_ssl_md5.h"
#include <sys/stat.h>

char			*ft_strto(char *string, int mode)
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

void	*ft_memjoin(void *dest, void *src, size_t d_len, size_t s_len)
{
    void *ret;

    if (!dest && !src)
        return (NULL);
    ret = ft_memalloc(d_len + s_len + 1);
    if (!ret)
        return (NULL);
    ft_memcpy(ret, dest, d_len);
    ft_memcpy(&ret[d_len], src, s_len);
    ft_memdel(&dest);
    return (ret);
}

void	md_read_from_fd(int fd, t_content *handler, size_t buf_size)
{
    void	*buf;
    ssize_t	bytes;

    buf = ft_memalloc(buf_size);
    handler->content = ft_memalloc(0);
    handler->cont_len = 0;
    while ((bytes = read(fd, buf, buf_size)) > 0)
    {
        handler->content = ft_memjoin(handler->content, buf,
                                  handler->cont_len, (size_t)bytes);
        handler->cont_len += bytes;
        ft_bzero(buf, buf_size);
    }
    ft_memdel(&buf);
}

unsigned long	ft_pow(size_t x, int pow)
{
	unsigned long res;

	res = 1;
	while (pow > 0)
	{
		res = res * x;
		pow--;
	}
	return (res);
}
