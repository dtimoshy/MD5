/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha224.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimoshy <dtimoshy@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 16:44:59 by dtimoshy          #+#    #+#             */
/*   Updated: 2018/10/29 16:45:00 by dtimoshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

extern const unsigned	g_256[];

static void				sha224_init_string_loop(
		unsigned int *tmp_arr, const unsigned char *string)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < 16)
	{
		tmp_arr[i] = (string[j] << 24) | (string[j + 1] << 16)
					 | (string[j + 2] << 8) | (string[j + 3]);
		i++;
		j += 4;
	}
	while (i < 64)
	{
		tmp_arr[i] = (((tmp_arr[i - 2] >> 17) | (tmp_arr[i - 2] << (32 - 17)))
				^ ((tmp_arr[i - 2] >> 19) | (tmp_arr[i - 2] << (32 - 19))) ^
				(tmp_arr[i - 2] >> 10)) + tmp_arr[i - 7];
		tmp_arr[i] += (((tmp_arr[i - 15] >> 7) | (tmp_arr[i - 15] << (32 - 7)))
				^ ((tmp_arr[i - 15] >> 18) | (tmp_arr[i - 15] << (32 - 18)))
				^ (tmp_arr[i - 15] >> 3)) + tmp_arr[i - 16];
		i++;
	}
}

static void				sha224_transform_loop(unsigned int *temp, unsigned int *tmp_arr)
{
	unsigned int	t1;
	unsigned int	t2;
	int i;

	i = -1;
	while (++i < 64)
	{
		t1 = temp[7] + (((temp[4] >> 6) | (temp[4] << (32 - 6)))
				^ ((temp[4] >> 11) | (temp[4] << (32 - 11))) ^
				((temp[4] >> 25) | (temp[4] << (32 - 25))));
		t1 += ((temp[4] & temp[5]) ^ (~temp[4] & temp[6])) + g_256[i] + tmp_arr[i];
		t2 = (((temp[0] >> 2) | (temp[0] << (32 - 2)))
				^ ((temp[0] >> 13) | (temp[0] << (32 - 13))) ^
				((temp[0] >> 22) | (temp[0] << (32 - 22))));
		t2 += ((temp[0] & temp[1]) ^ (temp[0] & temp[2]) ^
				(temp[1] & temp[2]));
		sha256_swap(temp, t1, t2);
	}
}

void					sha224_process(
		unsigned long *state, const unsigned char *string)
{
	unsigned int	tmp_arr[64];
	unsigned int	temp[8];
	int				i;

	sha224_init_string_loop(tmp_arr, string);
	i = -1;
	while (++i < 8)
		temp[i] = (unsigned int)state[i];
	sha224_transform_loop(temp, tmp_arr);
	i = -1;
	while (++i < 8)
		state[i] += temp[i];
}

unsigned char	*sha224_string_pad(t_content *string)
{
	size_t			bits;
	size_t			done_len;
	unsigned char	*done_str;
	int 			i;

	i = -1;
	bits = string->cont_len * 8;
	done_len = (((bits + 512 / 8) / 512) * 512 + 512) / 8;
	done_str = (unsigned char *)ft_memalloc(done_len);
	ft_memcpy(done_str, string->content, string->cont_len);
	done_str[string->cont_len] = 128;
	while (++i < 8)
		done_str[done_len - (8 - i)] = (unsigned char)(bits >> (8 * (7 - i)));
	string->cont_len = done_len;
	return (done_str);
}

void		sha224(t_content *string)
{
	unsigned char	*to_free;
	unsigned long	state[8];
	unsigned int	i;

	sha224_init(state);
	to_free = string->content;
	string->content = sha224_string_pad(string);
	ft_memdel((void **)&to_free);
	i = 0;
	while (i < string->cont_len)
	{
		sha224_process(state, string->content + i);
		i += 512 / 8;
	}
	i = 0;
	while (i < 7)
		ft_printf("%08x", state[i++]);
	ft_memdel((void **)&string->content);
}
