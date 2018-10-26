#include "ft_ssl_md5.h"

static unsigned int	*sha224_init_hash_values(void)
{
	unsigned int *hash_values;

	hash_values = (unsigned int *)malloc(8 * sizeof(unsigned int));
	hash_values[0] = 0xc1059ed8;
	hash_values[1] = 0x367cd507;
	hash_values[2] = 0x3070dd17;
	hash_values[3] = 0xf70e5939;
	hash_values[4] = 0xffc00b31;
	hash_values[5] = 0x68581511;
	hash_values[6] = 0x64f98fa7;
	hash_values[7] = 0xbefa4fa4;
	return (hash_values);
}

void				ssl_sha224(t_word *word, t_flags *flags)
{
	unsigned int	*k_arr;
	unsigned int	*hash_values;
	int				i;

	k_arr = sha256_init_k_arr();
	hash_values = sha224_init_hash_values();
	hash_values = sha256_start_processing(word, k_arr, hash_values);
	i = -1;
	while (++i < 7)
		if (flags->flag_b == 0)
			ft_printf("%.8x", hash_values[i]);
		else
			ft_printf("%.32b", hash_values[i]);
	free(k_arr);
	free(hash_values);
}
