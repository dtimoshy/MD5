#include "libft.h"

char	*ft_str_tolower(char *word)
{
	size_t i;

	i = 0;
	while (i < ft_strlen(word))
	{
		word[i] = ft_tolower(word[i]);
		i++;
	}
	return (word);
}
