/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512_algo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimoshy <dtimoshy@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 16:45:52 by dtimoshy          #+#    #+#             */
/*   Updated: 2018/10/29 16:45:53 by dtimoshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

#define ROTRIGHT64(a,b) (((a) >> (b)) | ((a) << (64-(b))))
#define EP0512(x) (ROTRIGHT64(x,28) ^ ROTRIGHT64(x,34) ^ ROTRIGHT64(x,39))
#define EP1512(x) (ROTRIGHT64(x,14) ^ ROTRIGHT64(x,18) ^ ROTRIGHT64(x,41))
#define SIG0512(x) (ROTRIGHT64(x,1) ^ ROTRIGHT64(x,8) ^ ((x) >> 7))
#define SIG1512(x) (ROTRIGHT64(x,19) ^ ROTRIGHT64(x,61) ^ ((x) >> 6))

static void		sha512_end_t_arr(unsigned long **t_arr)
{
	int				i;

	i = 16;
	while (i < 80)
	{
		t_arr[0][i] = t_arr[0][i - 16] + SIG0512(t_arr[0][i - 15]) +
				t_arr[0][i - 7] + SIG1512(t_arr[0][i - 2]);
		i++;
	}
}

static int		sha512_t_arr(t_content *string, unsigned long **t_arr,
				int appendix, size_t *size_done)
{
	unsigned long	len_now;
	int				i;
	int				k;
	size_t			rest;

	len_now = string->cont_len / 8 - (*size_done);
	i = 0;
	rest = 0;
	while (i < 16 && ++i && !(k = 0))
		while (k < 8 && ++k)
		{
			t_arr[0][i - 1] = (t_arr[0][i - 1] << 8) + string->content[0];
			(rest < len_now && ++rest) ? (string->content++) : 0;
		}
	(*size_done) += rest;
	if (len_now < 128 && appendix != 1)
		t_arr[0][rest / 8] += ft_pow(2, (8 - rest % 8) * 8 - 1);
	if (len_now < 112)
	{
		t_arr[0][14] = string->cont_len / ft_pow(2, 63);
		t_arr[0][15] = string->cont_len % ft_pow(2, 63);
	}
	sha512_end_t_arr(t_arr);
	return ((len_now < 128) + (len_now < 112));
}

static void		sha512_loop(unsigned long *temp,
				const unsigned long *k_arr, unsigned long *t_arr)
{
	int				i;
	unsigned long	tmp1;
	unsigned long	tmp2;

	i = 0;
	while (i < 80)
	{
		tmp1 = temp[7] + EP1512(temp[4]) + CH(temp[4], temp[5],
				temp[6]) + k_arr[i] + t_arr[i];
		tmp2 = EP0512(temp[0]) + MAJ(temp[0], temp[1], temp[2]);
		sha512_swap(&temp[0], tmp1, tmp2);
		i++;
	}
}

void			sha512_process(t_content *string, const unsigned long *k_arr,
				unsigned long *state)
{
	unsigned long	temp[8];
	unsigned long	*t_arr;
	int				i;
	int				current_done;
	size_t			size_done;

	current_done = 0;
	size_done = 0;
	while (current_done != 2)
	{
		i = -1;
		while (++i < 8)
			temp[i] = state[i];
		t_arr = (unsigned long *)malloc(sizeof(unsigned long) * 80);
		current_done = sha512_t_arr(string, &t_arr, current_done,
									&size_done);
		sha512_loop(temp, k_arr, t_arr);
		i = -1;
		while (++i < 8)
			state[i] += temp[i];
		free(t_arr);
	}
}
