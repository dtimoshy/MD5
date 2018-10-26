#include "ft_ssl_md5.h"

unsigned long		rot_r(unsigned long value, int amount, int bits)
{
	return ((value >> amount) | (value << (bits - amount)));
}

static unsigned int	*sha256_init_hash_values(void)
{
	unsigned int *hash_values;

	hash_values = (unsigned int *)malloc(8 * sizeof(unsigned int));
	hash_values[0] = 0x6a09e667;
	hash_values[1] = 0xbb67ae85;
	hash_values[2] = 0x3c6ef372;
	hash_values[3] = 0xa54ff53a;
	hash_values[4] = 0x510e527f;
	hash_values[5] = 0x9b05688c;
	hash_values[6] = 0x1f83d9ab;
	hash_values[7] = 0x5be0cd19;
	return (hash_values);
}

void				ssl_sha256(t_word *word, t_flags *flags)
{
	unsigned int	*k_arr;
	unsigned int	*hash_values;
	int				i;

	k_arr = sha256_init_k_arr();
	hash_values = sha256_init_hash_values();
	hash_values = sha256_start_processing(word, k_arr, hash_values);
	i = -1;
	while (++i < 8)
		if (flags->flag_b == 0)
			ft_printf("%.8x", hash_values[i]);
		else
			ft_printf("%.32b", hash_values[i]);
	free(k_arr);
	free(hash_values);
}
