#include <fcntl.h>
#include <unistd.h>
#include "ft_ssl_md5.h"
#include <sys/stat.h>

char	*ft_strto(char *word, int mode)
{
	size_t i;

	i = 0;
	while (i < ft_strlen(word))
	{
		if (mode == 0)
			word[i] = (char)ft_tolower(word[i]);
		if (mode == 1)
			word[i] = (char)ft_toupper(word[i]);
		i++;
	}
	return (word);
}

//void	ft_strunsdel(unsigned char **s)
//{
//	if (s && *s)
//	{
//		free(*s);
//		*s = NULL;
//	}
//}

//unsigned char	*ft_stralloc(size_t len)
//{
//	unsigned char	*res;
//	size_t			i;
//
//	res = (unsigned char *)malloc(len + 1);
//	i = 0;
//	while (i <= len)
//	{
//		res[i] = '\0';
//		i++;
//	}
//	return(res);
//}

t_content	*msg_from_fd(int fd, unsigned char **line)
{
	t_content			*word;
	unsigned char	*temp;
	size_t			ret;
	int				i;
	struct stat		st;
	size_t			len;

 	fstat(fd, &st);
 	word = (t_content *)malloc(sizeof(t_content));
 	ret = 0;
 	len = st.st_size;
 	if (fd == 0)
 		len = BUF_READ;
	temp = ft_strnew_unsigned(len);
	while ((i = read(fd, temp, len)) > 0)
	{
		ret += i;
        ft_strjoin_unsigned(line, temp, ret - i, i);
		ft_strdel_unsigned(&temp);
		temp = ft_strnew_unsigned(len);
	}
	ft_strdel_unsigned(&temp);
	word->content = *line;
	word->content_len = ret * 8;
	return (word);
}
