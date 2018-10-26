/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimoshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 13:03:19 by dtimoshy          #+#    #+#             */
/*   Updated: 2018/09/19 10:42:23 by dtimoshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <stdarg.h>
# include <stdlib.h>
// # include "../libft/libft.h"
# include <stdint.h>
# include <limits.h>

# define BUFF_SIZE 2
# define NO 0
# define HH 1
# define H 2
# define L 3
# define LL 4
# define J 5
# define Z 6

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

typedef struct		s_fd
{
	t_list			*buf;
	unsigned int	fd;
	unsigned int	no_read: 1;
	size_t			flag;
	struct s_fd		*next;
}					t_gnl;

typedef struct		s_pf
{
	short			right;
	short			zero;
	short			sign;
	short			space;
	short			hash;
	short			len;
	int				width;
	int				prec;
	char			spec;
}					t_pf;

int					get_next_line(const int fd, char **line);
int					ft_abs(int nbr);
int					ft_atoi(const char *str);
int					ft_atoi_base(const char *str, int str_base);
void				ft_bzero(void *s, size_t n);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
void				*ft_memalloc(size_t size);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				ft_memdel(void **ap);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memset(void *b, int c, size_t len);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strchr(const char *s, int c);
void				ft_strclr(char *s);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_strcpy(char *dst, const char *src);
void				ft_strdel(char **as);
char				*ft_strdup(const char *s);
int					ft_strequ(char const *s1, char const *s2);
void				ft_striter(char *s, void (*f)(char*));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strjoin(char const *s1, char const *s2);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
size_t				ft_strlen(const char *s);
size_t				ft_nbrlen(int nbr);
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_strncat(char *s1, const char *s2, size_t n);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strncpy(char *dst, const char *src, size_t len);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strnew(size_t size);
char				*ft_strnstr(const char *big, const char *lit, size_t len);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *big, const char *little);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strtrim(char const *s);
char				*ft_strrev(char *str);
int					ft_tolower(int c);
int					ft_toupper(int c);
void				ft_putchar(char c);
void				ft_putstr(char const *s);
void				ft_putendl(char const *s);
char				*ft_itoa(int n);
char				*ft_itoa_base(int n, int base);
void				ft_putnbr(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
char				**ft_strsplit(char const *s, char c);
t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
int					ft_isspace(int c);
void				ft_putstrarr(char **str);
void				ft_lstaddend(t_list **alst, t_list *new_list);
int					ft_countword_delim(char const *s, char c);
void				ft_strdelarr(char **strarr);
t_list				*ft_lstfind_nbr(t_list **alst, size_t num);
int					ft_isblank(int c);
int					ft_iscntrl(int c);
int					ft_isgraph(int c);
int					ft_islower(int c);
int					ft_ispunct(int c);
int					ft_isupper(int c);
void				ft_lstinsert(t_list **alst, t_list *new_list);
t_list				*ft_lstend(t_list **alst);
int					ft_lstlen(t_list **alst);
void				ft_lstreplace(t_list **alst, t_list *old_list, t_list *new);
void				ft_swap_nbr(void *nb1, void *nb2, size_t size);
int					ft_isnbr(char *str);
int					ft_perror(char *message);
void				ft_lstdelnod(t_list **alst);
int					ft_printf(const char *format, ...);
void				len_parse(const char **fmt, t_pf *pf);
void				spec_parse(const char **fmt, t_pf *pf);
int					handle_d(t_pf *pf, va_list args);
int					handle_u(t_pf *pf, va_list args);
int					handle_o(t_pf *pf, va_list args);
int					handle_x(t_pf *pf, va_list args);
int					handle_p(t_pf *pf, va_list args);
int					handle_bx(t_pf *pf, va_list args);
int					handle_other(t_pf *pf);
int					handle_char(t_pf *pf, va_list args);
int					handle_string(t_pf *pf, va_list args);
int					num_convert(t_pf *pf, va_list args);
int					char_convert(t_pf *pf, va_list args);
char				*wchar_get(wchar_t value);
char				*wstr_get(wchar_t *value, int prec);
char				*convert_base_d(size_t unsgnd, int base);
char				*convert_base_opux(size_t unsgnd, int base);
char				*convert_base_bx(size_t unsgnd, int base);
int					prec_check_print(int prec, size_t len, char **s, int mode);
char				*ft_str_to_upper(char *word);
unsigned char		*ft_str_unsigned_new(size_t len);
size_t				read_from_fd(int fd, unsigned char **line);
void				ft_str_unsigned_del(unsigned char **s);
void				ft_str_unsigned_concat(unsigned char **s1, unsigned char *s2, size_t l1, size_t l2);
unsigned long		ft_pow(size_t x, int pow);
char				*ft_str_tolower(char *word);

#endif
