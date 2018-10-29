/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_algo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimoshy <dtimoshy@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 16:45:20 by dtimoshy          #+#    #+#             */
/*   Updated: 2018/10/29 16:45:21 by dtimoshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

#define ROTRIGHT32(a,b) (((a) >> (b)) | ((a) << (32-(b))))
#define EP0256(x) (ROTRIGHT32(x,2) ^ ROTRIGHT32(x,13) ^ ROTRIGHT32(x,22))
#define EP1256(x) (ROTRIGHT32(x,6) ^ ROTRIGHT32(x,11) ^ ROTRIGHT32(x,25))
#define SIG0256(x) (ROTRIGHT32(x,7) ^ ROTRIGHT32(x,18) ^ ((x) >> 3))
#define SIG1256(x) (ROTRIGHT32(x,17) ^ ROTRIGHT32(x,19) ^ ((x) >> 10))

static void		sha256_end_t_arr(unsigned int **t_arr)
{
	int				i;

	i = 16;
	while (i < 64)
	{
		t_arr[0][i] = t_arr[0][i - 16] + SIG0256(t_arr[0][i - 15]) +
				t_arr[0][i - 7] + SIG1256(t_arr[0][i - 2]);
		i++;
	}
}

static int		sha256_t_arr(t_content *string, unsigned int **t_arr,
				int appendix, size_t *size_done)
{
	size_t			len_now;
	int				i;
	int				k;
	size_t			rest;

	i = -1;
	len_now = string->cont_len / 8 - (*size_done);
	rest = 0;
	while (++i < 16 && !(k = 0))
		while (k < 4 && ++k)
		{
			t_arr[0][i] = (t_arr[0][i] << 8) + string->content[0];
			(rest < len_now && ++rest) ? (string->content++) : 0;
		}
	(*size_done) += rest;
	if (len_now < 64 && appendix != 1)
		t_arr[0][rest / 4] +=
					(size_t)ft_pow(2, (4 - rest % 4) * 8 - 1);
	if (len_now < 56)
	{
		t_arr[0][14] = (unsigned int)string->cont_len / ft_pow(2, 31);
		t_arr[0][15] = (unsigned int)string->cont_len % ft_pow(2, 31);
	}
	sha256_end_t_arr(t_arr);
	return ((len_now < 64) + (len_now < 56));
}

static void		sha256_loop(unsigned int *temp,
				const unsigned int *k_arr, unsigned int *t_arr)
{
	int				i;
	unsigned int	tmp1;
	unsigned int	tmp2;

	i = 0;
	while (i < 64)
	{
		tmp1 = temp[7] + EP1256(temp[4]) + CH(temp[4], temp[5], temp[6]) +
				k_arr[i] + t_arr[i];
		tmp2 = EP0256(temp[0]) + MAJ(temp[0], temp[1], temp[2]);
		sha256_swap(&temp[0], tmp1, tmp2);
		i++;
	}
}

void			sha256_process(t_content *string, const unsigned int *k_arr,
				unsigned int *state)
{
	unsigned int	temp[8];
	unsigned int	*t_arr;
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
		t_arr = (unsigned int *)malloc(sizeof(unsigned int) * 64);
		current_done = sha256_t_arr(string, &t_arr, current_done,
									&size_done);
		sha256_loop(temp, k_arr, t_arr);
		i = -1;
		while (++i < 8)
			state[i] += temp[i];
		free(t_arr);
	}
}
