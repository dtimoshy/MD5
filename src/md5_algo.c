/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_algo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimoshy <dtimoshy@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 16:44:28 by dtimoshy          #+#    #+#             */
/*   Updated: 2018/10/29 16:44:29 by dtimoshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

#define A(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define B(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define C(x, y, z) ((x) ^ (y) ^ (z))
#define D(x, y, z) ((y) ^ ((x) | (~z)))
#define ROTLEFT32(x, n) (((x) << (n)) | ((x) >> (32-(n))))

static void			md5_loop(const int *s_arr, const unsigned int *k_arr,
								unsigned int *temp, unsigned int *t_arr)
{
	int				i;
	unsigned int	tmp;
	int				k;

	i = 0;
	while (i < 64)
	{
		tmp = 0;
		k = 0;
		if (i >= 0 && i <= 15 && (k = i) != -1)
			tmp = A(temp[1], temp[2], temp[3]);
		if (i >= 16 && i <= 31 && (k = (5 * i + 1) % 16) != -1)
			tmp = B(temp[1], temp[2], temp[3]);
		if (i >= 32 && i <= 47 && (k = (3 * i + 5) % 16) != -1)
			tmp = C(temp[1], temp[2], temp[3]);
		if (i >= 48 && i <= 63 && (k = (7 * i) % 16) != -1)
			tmp = D(temp[1], temp[2], temp[3]);
		tmp = tmp + temp[0] + k_arr[i] + t_arr[k];
		md5_swap(&temp[0], ROTLEFT32(tmp, s_arr[i]));
		i++;
	}
}

static int			md5_t_arr(t_content *string, unsigned int **t_arr,
								int appendix, size_t *size_done)
{
	int		i;
	int		k;
	size_t	rest;
	size_t	len_now;

	i = -1;
	len_now = string->cont_len / 8 - (*size_done);
	rest = 0;
	while (++i < 16 && !(k = 0)
		&& !(t_arr[0][i] = 0))
		while (k < 4 && ++k)
		{
			t_arr[0][i] = (string->content[0] << (8 * (k - 1))) + t_arr[0][i];
			(rest < len_now && ++rest) ? (string->content++) : 0;
		}
	(*size_done) += rest;
	if (len_now < 64 && appendix != 1)
		t_arr[0][rest / 4] += (size_t)ft_pow(2, (rest % 4 + 1) * 8 - 1);
	if (len_now < 56)
	{
		t_arr[0][14] = (unsigned int)string->cont_len % ft_pow(2, 31);
		t_arr[0][15] = (unsigned int)string->cont_len / ft_pow(2, 31);
		return (2);
	}
	return (len_now < 64);
}

void				md5_process(t_content *string, unsigned int *state,
						const int *s_arr, const unsigned int *k_arr)
{
	unsigned int	temp[4];
	int				i;
	unsigned int	*t_arr;
	int				current_done;
	size_t			size_done;

	current_done = 0;
	size_done = 0;
	while (current_done != 2)
	{
		i = -1;
		while (++i < 4)
			temp[i] = state[i];
		t_arr = (unsigned int *)malloc(16 * sizeof(unsigned int));
		current_done = md5_t_arr(string, &t_arr,
			current_done, &size_done);
		md5_loop(s_arr, k_arr, temp, t_arr);
		i = -1;
		while (++i < 4)
			state[i] += temp[i];
		free(t_arr);
	}
}
