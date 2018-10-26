#include "libft.h"

char	*ft_str_to_upper(char *word)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(word))
	{
		word[i] = ft_toupper(word[i]);
		i++;
	}
	return (word);
}
