#include "ft_ssl_md5.h"

static const t_ssl_mode		mode_change[] = {
	{ "md5", &md5},
	{"sha256", &sha256},
	{"sha224", &sha224},
	{"sha512", &sha512},
	{"sha384", &sha384},
	{ NULL, NULL}
};

void			ft_mode_error(char *cmd)
{
	int i;

	ft_printf("ft_ssl: Error: '%s' is an invalid command.\n\n\
Standart commands:\n\n", cmd);
	ft_printf("Message Digest commands:\n");
	i = 0;
	while (mode_change[i].name)
	{
		ft_printf("%s\n", mode_change[i].name);
		i++;
	}
	ft_printf("\nCipher commands:\n\n");
	exit(1);
}

void		ft_flag_error(t_flags *flags, char a, int mode)
{
	if (mode == 0)
		ft_printf("%s: illegal option -- %c\n", ft_strto(flags->name, 0), a);
	if (mode == 1)
		ft_printf("%s: option requires an argument -- s\n", flags->name);
	ft_printf("usage: %s [-pqr] [-s string] [files ...]\n", flags->name);
	ft_strdel(&flags->name);
	free(flags);
	exit(1);
}
