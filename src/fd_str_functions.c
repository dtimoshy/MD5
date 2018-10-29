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
			word[i] = ft_tolower(word[i]);
		if (mode == 1)
			word[i] = ft_toupper(word[i]);
		i++;
	}
	return (word);
}

void	ft_str_unsigned_del(unsigned char **s)
{
	if (s && *s)
	{
		free(*s);
		*s = NULL;
	}
}

unsigned char	*ft_str_unsigned_new(size_t len)
{
	unsigned char	*res;
	size_t			i;

	res = (unsigned char *)malloc(len + 1);
	i = 0;
	while (i <= len)
	{
		res[i] = '\0';
		i++;
	}
	return(res);
}

void	ft_strunsgncat2(unsigned char **s1, unsigned char *s2, size_t l1, size_t l2)
{
	unsigned char	*temp;
	size_t	i;

	temp = ft_str_unsigned_new(l1);
	i = 0;
	while (i < l1)
	{
		temp[i] = s1[0][i];
		i++;
	}
	if (*s1)
		ft_str_unsigned_del(s1);
	*s1 = ft_str_unsigned_new(l1 + l2);
	i = 0;
	while (i < l1)
	{
		s1[0][i] = temp[i];
		i++;
	}
	i = 0;
	while (i < l2)
	{
		s1[0][l1 + i] = s2[i];
		i++;
	}
	ft_str_unsigned_del(&temp);
}


t_word	*msg_from_fd(int fd, unsigned char **line)
{
	t_word			*word;
	unsigned char	*temp;
	size_t			ret;
	int				i;
	struct stat		st;
	size_t			len;

 	fstat(fd, &st);
 	word = (t_word *)malloc(sizeof(t_word));
 	ret = 0;
 	len = st.st_size;
 	(fd == 0) ? (len = 100) : 0;
	temp = ft_str_unsigned_new(len);
	while ((i = read(fd, temp, len)) > 0)
	{
		ret += i;
		ft_strunsgncat2(line, temp, ret - i, i);
		// ft_str_unsigned_concat(line, temp, ret - i, i);
		(temp) ? ft_str_unsigned_del(&temp) : 0;
		temp = ft_str_unsigned_new(st.st_size);
	}
	(temp) ? ft_str_unsigned_del(&temp) : 0;
	word->word = *line;
	word->length = ret * 8;
	return (word);
}

// void	ft_strunsgncat(unsigned char **s1, unsigned char *s2, size_t l1, size_t l2)
// {
// 	unsigned char	*temp;
// 	size_t	i;

// 	temp = ft_str_unsigned_new(l1);
// 	i = 0;
// 	while (i < l1)
// 	{
// 		temp[i] = s1[0][i];
// 		i++;
// 	}
// 	if (*s1)
// 		ft_str_unsigned_del(s1);
// 	*s1 = ft_str_unsigned_new(l1 + l2);
// 	i = 0;
// 	while (i < l1)
// 	{
// 		s1[0][i] = temp[i];
// 		i++;
// 	}
// 	i = 0;
// 	while (i < l2)
// 	{
// 		s1[0][l1 + i] = s2[i];
// 		i++;
// 	}
// 	ft_str_unsigned_del(&temp);
// }


// void	ft_str_unsigned_concat(unsigned char **s1, unsigned char *s2, size_t l1, size_t l2)
// {
// 	unsigned char	*temp;
// 	size_t	i;

// 	temp = ft_str_unsigned_new(l1);
// 	i = 0;
// 	while (i < l1 && ++i)
// 		temp[i - 1] = s1[0][i - 1];
// 	(*s1) ? ft_str_unsigned_del(s1) : 0;
// 	*s1 = ft_str_unsigned_new(l1 + l2);
// 	i = 0;
// 	while (i < l1 && ++i)
// 		s1[0][i - 1] = temp[i - 1];
// 	i = 0;
// 	while (i < l2 && ++i)
// 		s1[0][l1 + i - 1] = s2[i - 1];
// 	ft_str_unsigned_del(&temp);
// }

// size_t	read_from_fd(int fd, unsigned char **line)
// {
// 	unsigned char	*temp;
// 	size_t			ret;
// 	int				i;
// 	struct stat		st;
// 	size_t			length;

//  	fstat(fd, &st);
//  	ret = 0;
//  	length = st.st_size;
//  	(fd == 0) ? (length = 100) : 0;
// 	temp = ft_str_unsigned_new(length);
// 	while ((i = read(fd, temp, length)) > 0)
// 	{
// 		ret += i;
// 		ft_strunsgncat(line, temp, ret - i, i);
// 		// ft_str_unsigned_concat(line, temp, ret - i, i);
// 		(temp) ? ft_str_unsigned_del(&temp) : 0;
// 		temp = ft_str_unsigned_new(st.st_size);
// 	}
// 	(temp) ? ft_str_unsigned_del(&temp) : 0;
// 	return (ret);
// }