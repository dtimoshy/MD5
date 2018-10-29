#include "ft_ssl_md5.h"

static void		sha256_append_w_arr(unsigned int **w_arr)
{
	int				i;
	unsigned int	s0;
	unsigned int	s1;

	i = 16;
	while (i < 64)
	{
		s0 = rot_r(w_arr[0][i - 15], 7, 32) ^
			rot_r(w_arr[0][i - 15], 18, 32) ^ w_arr[0][i - 15] >> 3;
		s1 = rot_r(w_arr[0][i - 2], 17, 32) ^
			rot_r(w_arr[0][i - 2], 19, 32) ^ w_arr[0][i - 2] >> 10;
		w_arr[0][i] = w_arr[0][i - 16] + s0 + w_arr[0][i - 7] + s1;
		i++;
	}
}

static int		sha256_init_w_arr(t_content *word, unsigned int **w_arr,
			int append_one, size_t *processed_amount)
{
	size_t			curr_length;
	int				i;
	int				j;
	size_t			last_byte;

	curr_length = word->content_len / 8 - (*processed_amount);
	i = 0;
	last_byte = 0;
	while (i < 16 && ++i && !(j = 0))
		while (j < 4 && ++j)
		{
			w_arr[0][i - 1] = (w_arr[0][i - 1] << 8) + word->content[0];
			(last_byte < curr_length && ++last_byte) ? (word->content++) : 0;
		}
	(*processed_amount) += last_byte;
	if (curr_length < 64 && append_one != 1)
		w_arr[0][last_byte / 4] +=
					(size_t)ft_pow(2, (4 - last_byte % 4) * 8 - 1);
	if (curr_length < 56)
	{
		w_arr[0][14] = (unsigned int)word->content_len / ft_pow(2, 31);
		w_arr[0][15] = (unsigned int)word->content_len % ft_pow(2, 31);
	}
	sha256_append_w_arr(w_arr);
	return ((curr_length < 64) + (curr_length < 56));
}

static void		sha256_main_loop(unsigned int **temp,
	const unsigned int *k_arr, unsigned int *w_arr)
{
	int				i;
	unsigned int	temp1;
	unsigned int	temp2;

	i = 0;
	while (i < 64)
	{
		temp1 = temp[0][7] + (rot_r(temp[0][4], 6, 32) ^
			rot_r(temp[0][4], 11, 32) ^ rot_r(temp[0][4], 25, 32));
		temp1 += ((temp[0][4] & temp[0][5]) ^ (~temp[0][4] & temp[0][6]));
		temp1 += k_arr[i] + w_arr[i];
		temp2 = rot_r(temp[0][0], 2, 32) ^ rot_r(temp[0][0], 13, 32) ^
		rot_r(temp[0][0], 22, 32);
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

unsigned int	*sha256_process(t_content *word,
								const unsigned int *k_arr, unsigned int *hash_values)
{
	unsigned int	*temp_values;
	unsigned int	*w_arr;
	int				i;
	int				done_w_arr;
	size_t			processed_amount;

	done_w_arr = 0;
	processed_amount = 0;
	while (done_w_arr != 2)
	{
		i = 0;
		temp_values = (unsigned int *)malloc(8 * sizeof(unsigned int));
		while (i < 8 && ++i)
			temp_values[i - 1] = hash_values[i - 1];
		w_arr = (unsigned int *)malloc(64 * sizeof(unsigned int));
		done_w_arr = sha256_init_w_arr(word, &w_arr, done_w_arr,
			&processed_amount);
		sha256_main_loop(&temp_values, k_arr, w_arr);
		i = 0;
		while (i < 8 && ++i)
			hash_values[i - 1] += temp_values[i - 1];
		free(temp_values);
		free(w_arr);
	}
	return (hash_values);
}
