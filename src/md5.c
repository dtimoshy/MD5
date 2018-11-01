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

#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define K(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))
#define ROTLEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))

static const unsigned	g_s[] =
		{
				7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
				5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
				4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
				6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
		};

static const unsigned	g_k[] =
		{
				0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
				0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
				0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
				0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
				0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
				0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
				0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
				0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
				0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
				0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
				0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
				0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
				0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
				0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
				0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
				0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
		};

unsigned char	*msg_padding_md5(t_content *string)
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

void			md5_init(unsigned int *state)
{
	state[0] = 0x67452301;
	state[1] = 0xefcdab89;
	state[2] = 0x98badcfe;
	state[3] = 0x10325476;
}

static void		md5_transform(unsigned int *state, const unsigned int *string)
{
	unsigned int	temp[4];
	unsigned int	f;
	int				i;
	int				g;

	i = -1;
	while (++i < 4)
		temp[i] = state[i];
	i = -1;
	while (++i < 64)
	{
		if (i < 16 && (g = i) != -1)
			f = F(temp[1], temp[2], temp[3]);
		else if (i < 32 && (g = (5 * i + 1) % 16) != -1)
			f = G(temp[1], temp[2], temp[3]);
		else if (i < 48 && (g = (3 * i + 5) % 16) != -1)
			f = K(temp[1], temp[2], temp[3]);
		else if ((g = (7 * i) % 16) != -1)
			f = I(temp[1], temp[2], temp[3]);
		md5_swap(temp, ROTLEFT((temp[0] + f + g_k[i] + string[g]), g_s[i]));
	}
	i = -1;
	while (++i < 4)
		state[i] += temp[i];
}

unsigned int  swap_bytes(const unsigned int state)
{
	return (((state & 0xff000000) >> 24) |
			((state & 0x00ff0000) >> 8) |
			((state & 0x0000ff00) << 8) |
			((state & 0x000000ff) << 24));
}

void      md5(t_content *string)
{
	unsigned int  state[4];
	unsigned char *to_free;
	size_t      i;

	md5_init(state);
	to_free = string->content;
	string->content = msg_padding_md5(string);
	ft_memdel((void **)&to_free);
	i = 0;
	while (i < string->cont_len)
	{
		md5_transform(state, (const unsigned int *)(string->content + i));
		i += 512 / 8;
	}
	i = 0;
	while (i < 4)
		ft_printf("%08x", swap_bytes(state[i++]));
	ft_memdel((void **)&string->content);
}
