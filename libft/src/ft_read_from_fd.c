#include <fcntl.h>
#include <unistd.h>
#include "libft.h"
#include <sys/stat.h>

size_t	read_from_fd(int fd, unsigned char **line)
{
	unsigned char	*temp;
	size_t			ret;
	int				i;
	struct stat		st;
	size_t			length;

 	fstat(fd, &st);
 	ret = 0;
 	length = st.st_size;
 	(fd == 0) ? (length = 100) : 0;
	temp = ft_str_unsigned_new(length);
	while ((i = read(fd, temp, length)) > 0)
	{
		ret += i;
		ft_str_unsigned_concat(line, temp, ret - i, i);
		(temp) ? ft_str_unsigned_del(&temp) : 0;
		temp = ft_str_unsigned_new(st.st_size);
	}
	(temp) ? ft_str_unsigned_del(&temp) : 0;
	return (ret);
}
