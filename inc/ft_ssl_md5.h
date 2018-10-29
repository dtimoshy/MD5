#ifndef FT_SSL_MD5_H
# define FT_SSL_MD5_H
# include "libft.h"
# define BUF_READ 4096

typedef struct		s_word
{
	unsigned char	*word;
	size_t			length;
	
}					t_word;

typedef struct		s_flags
{
	char	*name;
	void	(*f)(t_word *word);
	char	flag_r;
	char	flag_q;
	int		flag_p;
	char	flag_b;
	char	write_from_stdin;
	char	read_from_fd;
}					t_flags;

typedef struct			s_ssl_mode
{
	char				*name;
	void				(*f)(t_word *word);
}						t_ssl_mode;

void				md5(t_word *word);
void				parce_args(t_flags *flags, char **av, int ac);
void				sha256(t_word *word);
void				sha224(t_word *word);
void				sha512(t_word *word);
void				sha384(t_word *word);
unsigned int		*md5_start_processing(t_word *word, unsigned int *hash_values,
					const int *s_arr, const unsigned int *k_arr);
unsigned int		*sha256_start_processing(t_word *word, const unsigned int *k_arr, unsigned int *hash_values);
unsigned long		rot_r(unsigned long value, int amount, int bits);
unsigned long		*sha512_start_processing(t_word *word, const unsigned long *k_arr, unsigned long *hash_values);
void				ft_mode_error(char *cmd);
void				ft_flag_error(t_flags *flags, char a, int mode);
char				*ft_strto(char *word, int mode);
void				ft_str_unsigned_del(unsigned char **s);
unsigned char		*ft_str_unsigned_new(size_t len);
void				ft_str_unsigned_concat(unsigned char **s1, unsigned char *s2, size_t l1, size_t l2);
size_t				read_from_fd(int fd, unsigned char **line);
t_word				*msg_from_fd(int fd, unsigned char **line);

#endif
