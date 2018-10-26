#include "libft.h"

void	ft_str_unsigned_del(unsigned char **s)
{
	if (s && *s)
	{
		free(*s);
		*s = NULL;
	}
}
