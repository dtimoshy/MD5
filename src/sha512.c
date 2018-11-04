/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimoshy <dtimoshy@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 16:45:42 by dtimoshy          #+#    #+#             */
/*   Updated: 2018/10/29 16:45:43 by dtimoshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

extern unsigned long	g_512[];

static void				sha512_init_string(unsigned long *tmp_arr,
				const unsigned char *string)
{
	int i;
	int j;

	i = 0;
	while (i < 16)
	{
		j = 0;
		while (j++ < 8)
		{
			tmp_arr[i] = (tmp_arr[i] << 8) + *string;
			string++;
		}
		i++;
	}
	while (i < 80)
	{
		tmp_arr[i] = (((tmp_arr[i - 2] >> 19) | (tmp_arr[i - 2] << (64 - 19)))
			^ ((tmp_arr[i - 2] >> 61) | (tmp_arr[i - 2] << (64 - 61))) ^
			(tmp_arr[i - 2] >> 6)) + tmp_arr[i - 7];
		tmp_arr[i] += (((tmp_arr[i - 15] >> 1) | (tmp_arr[i - 15] << (64 - 1)))
			^ ((tmp_arr[i - 15] >> 8) | (tmp_arr[i - 15] << (64 - 8)))
			^ (tmp_arr[i - 15] >> 7)) + tmp_arr[i - 16];
		i++;
	}
}

static void				sha512_transform_loop(unsigned long *temp,
						unsigned long *tmp_arr)
{
	unsigned long	t1;
	unsigned long	t2;
	int				i;

	i = -1;
	while (++i < 80)
	{
		t1 = temp[7] + (((temp[4] >> 14) | (temp[4] << (64 - 14)))
			^ ((temp[4] >> 18) | (temp[4] << (64 - 18))) ^
			((temp[4] >> 41) | (temp[4] << (64 - 41))));
		t1 += ((temp[4] & temp[5]) ^ (~temp[4] & temp[6]))
		+ g_512[i] + tmp_arr[i];
		t2 = (((temp[0] >> 28) | (temp[0] << (64 - 28)))
			^ ((temp[0] >> 34) | (temp[0] << (64 - 34))) ^
			((temp[0] >> 39) | (temp[0] << (64 - 39))));
		t2 += ((temp[0] & temp[1]) ^ (temp[0] & temp[2]) ^
			(temp[1] & temp[2]));
		sha512_swap(temp, t1, t2);
	}
}

static void				sha512_process(unsigned long *state,
				const unsigned char *string)
{
	unsigned long	tmp_arr[80];
	unsigned long	temp[8];
	int				i;

	sha512_init_string(tmp_arr, string);
	i = -1;
	while (++i < 8)
		temp[i] = state[i];
	sha512_transform_loop(temp, tmp_arr);
	i = -1;
	while (++i < 8)
		state[i] += temp[i];
}

unsigned char			*sha512_string_pad(t_content *string)
{
	size_t			bits;
	size_t			done_len;
	unsigned char	*done_str;
	int				i;

	i = -1;
	bits = (string->cont_len) * 8;
	done_len = (((bits + 1024 / 8) / 1024) * 1024 + 1024) / 8;
	done_str = (unsigned char *)ft_memalloc(done_len);
	ft_memcpy(done_str, string->content, string->cont_len);
	done_str[string->cont_len] = 128;
	while (++i < 8)
		done_str[done_len - (8 - i)] = (unsigned char)(bits >> (8 * (7 - i)));
	string->cont_len = done_len;
	return (done_str);
}

void					sha512(t_content *string)
{
	unsigned long	state[8];
	unsigned char	*to_free;
	unsigned int	i;

	sha512_init(state);
	to_free = string->content;
	string->content = sha512_string_pad(string);
	ft_memdel((void **)&to_free);
	i = 0;
	while (i < string->cont_len)
	{
		sha512_process(state, string->content + i);
		i += 1024 / 8;
	}
	i = 0;
	while (i < 8)
		ft_printf("%016lx", state[i++]);
	ft_memdel((void **)&string->content);
}
