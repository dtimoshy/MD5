#include "ft_ssl_md5.h"

void	md5_init(unsigned int *state)
{
	state[0] = 0x67452301;
	state[1] = 0xefcdab89;
	state[2] = 0x98badcfe;
	state[3] = 0x10325476;
}

void	sha224_init(unsigned long *state)
{
	state[0] = 0xc1059ed8;
	state[1] = 0x367cd507;
	state[2] = 0x3070dd17;
	state[3] = 0xf70e5939;
	state[4] = 0xffc00b31;
	state[5] = 0x68581511;
	state[6] = 0x64f98fa7;
	state[7] = 0xbefa4fa4;
}

void	sha256_init(unsigned long *state)
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

void	sha384_init(unsigned long *state)
{
	state[0] = 0xcbbb9d5dc1059ed8;
	state[1] = 0x629a292a367cd507;
	state[2] = 0x9159015a3070dd17;
	state[3] = 0x152fecd8f70e5939;
	state[4] = 0x67332667ffc00b31;
	state[5] = 0x8eb44a8768581511;
	state[6] = 0xdb0c2e0d64f98fa7;
	state[7] = 0x47b5481dbefa4fa4;
}

void	sha512_init(unsigned long *state)
{
	state[0] = 0x6a09e667f3bcc908;
	state[1] = 0xbb67ae8584caa73b;
	state[2] = 0x3c6ef372fe94f82b;
	state[3] = 0xa54ff53a5f1d36f1;
	state[4] = 0x510e527fade682d1;
	state[5] = 0x9b05688c2b3e6c1f;
	state[6] = 0x1f83d9abfb41bd6b;
	state[7] = 0x5be0cd19137e2179;
}
