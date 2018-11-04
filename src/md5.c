/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimoshy <dtimoshy@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 16:44:19 by dtimoshy          #+#    #+#             */
/*   Updated: 2018/10/29 16:44:21 by dtimoshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

extern const unsigned	g_smd5[];

extern const unsigned	g_kmd5[];

static void				md5_transform_loop(unsigned int *temp,
						const unsigned int *string)
{
	unsigned int	k;
	int				g;
	int				i;

	i = -1;
	while (++i < 64)
	{
		if (i < 16 && (g = i) != -1)
			k = (temp[1] & temp[2]) | (~temp[1] & temp[3]);
		else if (i < 32 && (g = (5 * i + 1) % 16) != -1)
			k = (temp[1] & temp[3]) | (temp[2] & ~temp[3]);
		else if (i < 48 && (g = (3 * i + 5) % 16) != -1)
			k = temp[1] ^ temp[2] ^ temp[3];
		else if ((g = (7 * i) % 16) != -1)
			k = temp[2] ^ (temp[1] | ~temp[3]);
		md5_swap(temp, ((temp[0] + k + g_kmd5[i] + string[g]) << g_smd5[i])
			| ((temp[0] + k + g_kmd5[i] + string[g])
				>> (32 - g_smd5[i])));
	}
}

static void				md5_process(unsigned int *state,
						const unsigned int *string)
{
	unsigned int	temp[4];
	int				i;

	i = -1;
	while (++i < 4)
		temp[i] = state[i];
	md5_transform_loop(temp, string);
	i = -1;
	while (++i < 4)
		state[i] += temp[i];
}

unsigned int			md5_swap_bytes(const unsigned int state)
{
	return (((state & 0xff000000) >> 24) |
			((state & 0x00ff0000) >> 8) |
			((state & 0x0000ff00) << 8) |
			((state & 0x000000ff) << 24));
}

unsigned char			*md5_string_pad(t_content *string)
{
	size_t			bits;
	size_t			done_len;
	unsigned char	*done_str;
	int				i;

	i = -1;
	bits = (string->cont_len) * 8;
	done_len = (((bits + 512 / 8) / 512) * 512 + 512) / 8;
	done_str = (unsigned char *)ft_memalloc(done_len);
	ft_memcpy(done_str, string->content, string->cont_len);
	done_str[string->cont_len] = 128;
	while (++i < 8)
		done_str[done_len - (i + 1)] = (unsigned char)(bits >> (8 * (7 - i)));
	string->cont_len = done_len;
	return (done_str);
}

void					md5(t_content *string)
{
	unsigned int	state[4];
	unsigned char	*to_free;
	size_t			i;

	md5_init(state);
	to_free = string->content;
	string->content = md5_string_pad(string);
	ft_memdel((void **)&to_free);
	i = 0;
	while (i < string->cont_len)
	{
		md5_process(state, (const unsigned int *)(string->content + i));
		i += 512 / 8;
	}
	i = 0;
	while (i < 4)
		ft_printf("%08x", md5_swap_bytes(state[i++]));
	ft_memdel((void **)&string->content);
}
