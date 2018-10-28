#include "ft_ssl_md5.h"

static unsigned int	assign_f(unsigned int *temp_vars, int i,
	const unsigned int *k_arr, unsigned int *m_arr)
{
	unsigned int	f;
	int				g;

	g = 0;
	f = 0;
	if (i >= 0 && i <= 15 && (g = i) != -1)
		f = (temp_vars[1] & temp_vars[2]) | ((~temp_vars[1]) & temp_vars[3]);
	if (i >= 16 && i <= 31 && (g = (5 * i + 1) % 16) != -1)
		f = (temp_vars[3] & temp_vars[1]) | ((~temp_vars[3]) & temp_vars[2]);
	if (i >= 32 && i <= 47 && (g = (3 * i + 5) % 16) != -1)
		f = temp_vars[1] ^ temp_vars[2] ^ temp_vars[3];
	if (i >= 48 && i <= 63 && (g = (7 * i) % 16) != -1)
		f = temp_vars[2] ^ (temp_vars[1] | (~temp_vars[3]));
	f = f + temp_vars[0] + k_arr[i] + m_arr[g];
	return (f);
}

static void			md5_main_loop(const int *s_arr, const unsigned int *k_arr,
			unsigned int **temp_vars, unsigned int *m_arr)
{
	int				i;
	unsigned int	f;

	i = 0;
	while (i < 64)
	{
		f = assign_f(temp_vars[0], i, k_arr, m_arr);
		temp_vars[0][0] = temp_vars[0][3];
		temp_vars[0][3] = temp_vars[0][2];
		temp_vars[0][2] = temp_vars[0][1];
		temp_vars[0][1] = temp_vars[0][1] +
		((f << s_arr[i]) | f >> (32 - s_arr[i]));
		i++;
	}
}

static int			md5_init_m_arr(t_word *word, unsigned int **m_arr,
	int append_one, size_t *processed_amount)
{
	int		i;
	int		j;
	size_t	last;
	size_t	curr_length;

	i = -1;
	curr_length = word->length / 8 - (*processed_amount);
	last = 0;
	while (++i < 16 && !(j = 0) &&
		!(m_arr[0][i] = 0))
		while (j < 4 && ++j)
		{
			m_arr[0][i] = (word->word[0] << (8 * (j - 1))) + m_arr[0][i];
			(last < curr_length && ++last) ? (word->word++) : 0;
		}
	(*processed_amount) += last;
	if (curr_length < 64 && append_one != 1)
		m_arr[0][last / 4] += (size_t)ft_pow(2, (last % 4 + 1) * 8 - 1);
	if (curr_length < 56)
	{
		m_arr[0][14] = (unsigned int)word->length % ft_pow(2, 31);
		m_arr[0][15] = (unsigned int)word->length / ft_pow(2, 31);
		return (2);
	}
	return (curr_length < 64);
}

unsigned int		*md5_start_processing(t_word *word,
				unsigned int *hash_values, const int *s_arr, const unsigned int *k_arr)
{
	unsigned int	*temp_vars;
	int				i;
	unsigned int	*m_arr;
	int				done_with_m_arr;
	size_t			processed_amount;

	done_with_m_arr = 0;
	processed_amount = 0;
	while (done_with_m_arr != 2)
	{
		temp_vars = (unsigned int *)malloc(4 * sizeof(unsigned int));
		i = 0;
		while (i < 4 && ++i)
			temp_vars[i - 1] = hash_values[i - 1];
		m_arr = (unsigned int *)malloc(16 * sizeof(unsigned int));
		(done_with_m_arr = md5_init_m_arr(word, &m_arr,
			done_with_m_arr, &processed_amount));
		md5_main_loop(s_arr, k_arr, &temp_vars, m_arr);
		i = 0;
		while (i < 4 && ++i)
			hash_values[i - 1] += temp_vars[i - 1];
		free(temp_vars);
		free(m_arr);
	}
	return (hash_values);
}
