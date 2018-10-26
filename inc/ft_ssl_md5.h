#ifndef FT_SSL_MD5_H
# define FT_SSL_MD5_H
# include "libft.h"
# define BUF_READ 100000

typedef struct		s_word
{
	unsigned char	*word;
	size_t			length;
	
}					t_word;

typedef struct		s_flags
{
	char	*name;
	void	(*f)(t_word *word, struct s_flags *flags);
	char	flag_r;
	char	flag_q;
	int		flag_p;
	char	flag_b;
	char	write_from_stdin;
	char	read_from_fd;
}					t_flags;

typedef struct			s_md5_stack
{
	char				*name;
	void				(*f)(t_word *word, struct s_flags *flags);
	struct s_md5_stack	*next;

}						t_md5_stack;

void				start_md5_processing(int ac, char **av, char read_from_fd);
void				ssl_md5(t_word *word, t_flags *flags);
void				ssl_sha256(t_word *word, t_flags *flags);
void				ssl_sha224(t_word *word, t_flags *flags);
void				ssl_sha512(t_word *word, t_flags *flags);
void				ssl_sha384(t_word *word, t_flags *flags);
unsigned int		*md5_start_processing(t_word *word, unsigned int *hash_values,
					int *s_arr, unsigned int *k_arr);
unsigned int		*sha256_start_processing(t_word *word, unsigned int *k_arr, unsigned int *hash_values);
unsigned int		*sha256_init_k_arr(void);
unsigned long		rot_r(unsigned long value, int amount, int bits);
int					parce_flags(t_flags *flags, char **av, int ac, int *i);
unsigned long		*sha512_start_processing(t_word *word, unsigned long *k_arr, unsigned long *hash_values);
unsigned long		*sha512_init_k_arr(void);
t_md5_stack			*make_md5_stack(void);
void				from_fd(t_flags *flags, int fd, char *name);

#endif
