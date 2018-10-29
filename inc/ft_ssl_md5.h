/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_md5.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimoshy <dtimoshy@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 17:30:28 by dtimoshy          #+#    #+#             */
/*   Updated: 2018/10/29 17:30:30 by dtimoshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_MD5_H
# define FT_SSL_MD5_H
# include "libft.h"
# define BUF_READ 200
# define CH(x,y,z) (((x) & (y)) ^ (~(x) & (z)))
# define MAJ(x,y,z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))

typedef struct		s_content
{
	unsigned char	*content;
	size_t			cont_len;
}					t_content;

typedef struct		s_ssl_md5
{
	char			*name;
	void			(*f)(t_content *word);
	int				r;
	int				q;
	int				p;
	int				stdin_write;
}					t_ssl_md5;

typedef struct		s_ssl_mode
{
	char			*name;
	void			(*f)(t_content *content);
}					t_ssl_mode;

void				parse_arguments(t_ssl_md5 *handler, char **argv, int argc);
void				parse_s_string(t_ssl_md5 *handler, char **argv,
					int *i, int *k);
void				msg_from_fd(int fd, unsigned char **line,
					t_content *string);
void				ft_mode_error(char *cmd);
void				ft_flag_error(t_ssl_md5 *flags, char a, int mode);
void				ft_error_opening(char *name, char *func, char *error);
char				*ft_strto(char *string, int mode);
void				md5(t_content *word);
void				sha256(t_content *string);
void				sha224(t_content *string);
void				sha512(t_content *string);
void				sha384(t_content *string);
void				md5_process(t_content *word, unsigned int *hash_values,
					const int *s_arr, const unsigned int *k_arr);
void				sha256_process(t_content *string, const unsigned int *k_arr,
					unsigned int *state);
void				sha512_process(t_content *string,
					const unsigned long *k_arr, unsigned long *state);
unsigned long		ft_pow(size_t x, int pow);
void				md5_swap(unsigned int *vars, unsigned rotleft);
void				sha256_swap(unsigned int *vars, unsigned int temp1,
					unsigned int temp2);
void				sha512_swap(unsigned long *vars, unsigned long temp1,
					unsigned long temp2);

#endif
