#include "libft.h"

unsigned long	ft_pow(size_t x, int pow)
{
	unsigned long res;

	res = 1;
	while (pow > 0)
	{
		res = res * x;
		pow--;
	}
	return (res);
}
