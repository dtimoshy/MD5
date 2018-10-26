#include "ft_ssl_md5.h"

static unsigned long	*sha384_init_hash_values(void)
{
	unsigned long *hash_values;

	hash_values = (unsigned long *)malloc(8 * sizeof(unsigned long));
	hash_values[0] = 0xcbbb9d5dc1059ed8;
	hash_values[1] = 0x629a292a367cd507;
	hash_values[2] = 0x9159015a3070dd17;
	hash_values[3] = 0x152fecd8f70e5939;
	hash_values[4] = 0x67332667ffc00b31;
	hash_values[5] = 0x8eb44a8768581511;
	hash_values[6] = 0xdb0c2e0d64f98fa7;
	hash_values[7] = 0x47b5481dbefa4fa4;
	return (hash_values);
}

void					ssl_sha384(t_word *word, t_flags *flags)
{
	unsigned long	*k_arr;
	unsigned long	*hash_values;
	int				i;

	k_arr = sha512_init_k_arr();
	hash_values = sha384_init_hash_values();
	hash_values = sha512_start_processing(word, k_arr, hash_values);
	i = -1;
	while (++i < 6)
		if (flags->flag_b == 0)
			ft_printf("%.16lx", hash_values[i]);
		else
			ft_printf("%.64lb", hash_values[i]);
	free(k_arr);
	free(hash_values);
}
