/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimoshy <dtimoshy@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 16:45:09 by dtimoshy          #+#    #+#             */
/*   Updated: 2018/10/29 16:45:10 by dtimoshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

#define ROTRIGHT32(a,b) (((a) >> (b)) | ((a) << (32-(b))))
#define EP0(x) (ROTRIGHT32(x,2) ^ ROTRIGHT32(x,13) ^ ROTRIGHT32(x,22))
#define EP1(x) (ROTRIGHT32(x,6) ^ ROTRIGHT32(x,11) ^ ROTRIGHT32(x,25))
#define SIG0(x) (ROTRIGHT32(x,7) ^ ROTRIGHT32(x,18) ^ ((x) >> 3))
#define SIG1(x) (ROTRIGHT32(x,17) ^ ROTRIGHT32(x,19) ^ ((x) >> 10))

static const unsigned	g_256[] =
        {
                0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1,
                0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
                0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 0xe49b69c1, 0xefbe4786,
                0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
                0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147,
                0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
                0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b,
                0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
                0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a,
                0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
                0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
        };

static void				sha256_init(unsigned long *state)
{
    state[0] = 0x6a09e667;
    state[1] = 0xbb67ae85;
    state[2] = 0x3c6ef372;
    state[3] = 0xa54ff53a;
    state[4] = 0x510e527f;
    state[5] = 0x9b05688c;
    state[6] = 0x1f83d9ab;
    state[7] = 0x5be0cd19;
}

unsigned char *msg_padding_256(t_content *string)
{
	size_t			bits;
	size_t			done_len;
	unsigned char	*done_str;
	int 			i;

	i = -1;
	bits = (string->cont_len) * 8;
	done_len = (((bits + 512 / 8) / 512) * 512 + 512) / 8;
	done_str = (unsigned char *)ft_memalloc(done_len);
	ft_memcpy(done_str, string->content, string->cont_len);
	done_str[string->cont_len] = 128;
	while (++i < 8)
		done_str[done_len - (8 - i)] = (unsigned char)(bits >> (8 * (7 - i)));
	string->cont_len = done_len;
	return (done_str);
}

static void				sha256_init_msg_schedule(
		unsigned int *m, const unsigned char *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < 16)
	{
		m[i] = (data[j] << 24) | (data[j + 1] << 16)
			   | (data[j + 2] << 8) | (data[j + 3]);
		i++;
		j += 4;
	}
	while (i < 64)
	{
		m[i] = SIG1(m[i - 2]) + m[i - 7] + SIG0(m[i - 15]) + m[i - 16];
		i++;
	}
}

void					sha256_transform(
		unsigned long *state, const unsigned char *data)
{
	unsigned int	temp1;
	unsigned int	temp2;
	unsigned int	m[64];
	unsigned int	vars[8];
	int				i;

	sha256_init_msg_schedule(m, data);
	i = -1;
	while (++i < 8)
		vars[i] = (unsigned int)state[i];
	i = -1;
	while (++i < 64)
	{
		temp1 = vars[7] + EP1(vars[4])
				+ CH(vars[4], vars[5], vars[6]) + g_256[i] + m[i];
		temp2 = EP0(vars[0]) + MAJ(vars[0], vars[1], vars[2]);
		sha256_swap(vars, temp1, temp2);
	}
	i = -1;
	while (++i < 8)
		state[i] += vars[i];
}

void					sha256(t_content *string)
{
	unsigned long	state[8];
	unsigned char	*to_free;
	unsigned int	i;

	sha256_init(state);
	to_free = string->content;
	string->content = msg_padding_256(string);
	ft_memdel((void **)&to_free);
	i = 0;
	while (i < string->cont_len)
	{
		sha256_transform(state, string->content + i);
		i += 512 / 8;
	}
	i = 0;
	while (i < 8)
		ft_printf("%08x", state[i++]);
	ft_memdel((void **)&string->content);
}
