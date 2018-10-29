#include "ft_ssl_md5.h"

static void		sha512_append_w_arr(unsigned long **w_arr)
{
	int				i;
	unsigned long	s0;
	unsigned long	s1;

	i = 16;
	while (i < 80)
	{
		s0 = rot_r(w_arr[0][i - 15], 1, 64) ^
			rot_r(w_arr[0][i - 15], 8, 64) ^ w_arr[0][i - 15] >> 7;
		s1 = rot_r(w_arr[0][i - 2], 19, 64) ^
			rot_r(w_arr[0][i - 2], 61, 64) ^ w_arr[0][i - 2] >> 6;
		w_arr[0][i] = w_arr[0][i - 16] + s0 + w_arr[0][i - 7] + s1;
		i++;
	}
}

static int		sha512_init_w_arr(t_content *word, unsigned long **w_arr,
		int append_one, size_t *processed_amount)
{
	unsigned long	curr_length;
	int				i;
	int				j;
	size_t			last_byte;

	curr_length = word->content_len / 8 - (*processed_amount);
	i = 0;
	last_byte = 0;
	while (i < 16 && ++i && !(j = 0))
		while (j < 8 && ++j)
		{
			w_arr[0][i - 1] = (w_arr[0][i - 1] << 8) + word->content[0];
			(last_byte < curr_length && ++last_byte) ? (word->content++) : 0;
		}
	(*processed_amount) += last_byte;
	if (curr_length < 128 && append_one != 1)
		w_arr[0][last_byte / 8] += ft_pow(2, (8 - last_byte % 8) * 8 - 1);
	if (curr_length < 112)
	{
		w_arr[0][14] = word->content_len / ft_pow(2, 63);
		w_arr[0][15] = word->content_len % ft_pow(2, 63);
	}
	sha512_append_w_arr(w_arr);
	return ((curr_length < 128) + (curr_length < 112));
}

static void		sha512_main_loop(unsigned long **temp,
	const unsigned long *k_arr, unsigned long *w_arr)
{
	int				i;
	unsigned long	temp1;
	unsigned long	temp2;

	i = 0;
	while (i < 80)
	{
		temp1 = temp[0][7] + (rot_r(temp[0][4], 14, 64) ^
			rot_r(temp[0][4], 18, 64) ^ rot_r(temp[0][4], 41, 64));
		temp1 += ((temp[0][4] & temp[0][5]) ^ (~temp[0][4] & temp[0][6]));
		temp1 += k_arr[i] + w_arr[i];
		temp2 = rot_r(temp[0][0], 28, 64) ^ rot_r(temp[0][0], 34, 64) ^
		rot_r(temp[0][0], 39, 64);
		temp2 += (temp[0][0] & temp[0][1]) ^ (temp[0][0] & temp[0][2]) ^
		(temp[0][1] & temp[0][2]);
		temp[0][7] = temp[0][6];
		temp[0][6] = temp[0][5];
		temp[0][5] = temp[0][4];
		temp[0][4] = temp[0][3] + temp1;
		temp[0][3] = temp[0][2];
		temp[0][2] = temp[0][1];
		temp[0][1] = temp[0][0];
		temp[0][0] = temp1 + temp2;
		i++;
	}
}

unsigned long	*sha512_process(t_content *word,
								 const unsigned long *k_arr, unsigned long *hash_values)
{
	unsigned long	*temp_values;
	unsigned long	*w_arr;
	int				i;
	int				done_w_arr;
	size_t			processed_amount;

	done_w_arr = 0;
	processed_amount = 0;
	while (done_w_arr != 2)
	{
		i = 0;
		temp_values = (unsigned long *)malloc(8 * sizeof(unsigned long));
		while (i < 8 && ++i)
			temp_values[i - 1] = hash_values[i - 1];
		w_arr = (unsigned long *)malloc(80 * sizeof(unsigned long));
		done_w_arr = sha512_init_w_arr(word, &w_arr, done_w_arr,
					&processed_amount);
		sha512_main_loop(&temp_values, k_arr, w_arr);
		i = 0;
		while (i < 8 && ++i)
			hash_values[i - 1] += temp_values[i - 1];
		free(temp_values);
		free(w_arr);
	}
	return (hash_values);
}

