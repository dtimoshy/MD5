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

void			msg_from_fd(int fd, unsigned char **line, t_content *string)
{
	unsigned char	*temp;
	size_t			ret;
	int				i;
	struct stat		st;
	size_t			len;

	fstat(fd, &st);
	ret = 0;
	len = st.st_size;
	if (fd == 0)
		len = BUF_READ;
	temp = ft_strnew_unsigned(len);
	while ((i = read(fd, temp, len)) > 0)
	{
		ret += i;
		ft_strjoin_unsigned(line, temp, ret - i, i);
		ft_strdel_unsigned(&temp);
		temp = ft_strnew_unsigned(len);
	}
	ft_strdel_unsigned(&temp);
	string->content = *line;
	string->cont_len = ret * 8;
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
