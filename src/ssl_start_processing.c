#include <fcntl.h>
#include "ft_ssl_md5.h"
#include <unistd.h>
#include <errno.h>

static const t_md5_stack		mode_change[] = {
	{ "md5", &ssl_md5},
	{"sha256", &ssl_sha256},
	{"sha224", &ssl_sha224},
	{"sha512", &ssl_sha512},
	{"sha384", &ssl_sha384},
	{ NULL, NULL}
};

static void		read_from_files(int i, char **av, int ac, t_flags *flags)
{
	int fd;

	while (i < ac && ++flags->write_from_stdin)
	{
		fd = open(av[i], O_RDONLY);
		if (fd < 0 || read(fd, 0, 0) < 0)
			ft_printf("%s: %s: %s\n", ft_str_tolower(flags->name), av[i], strerror(errno));
		else
			from_fd(flags, fd, av[i]);
		i++;
		close(fd);
	}
}

static void		parce_args(t_flags *flags, char **av, int ac)
{
	int i;
	int temp;

	i = 0;
	while (++i < ac)
		if (av[i][0] == '-' && av[i][1])
		{
			temp = parce_flags(flags, av, ac, &i);
			if (temp == -1)
				exit(0);
			if (temp == -2)
				return ;
		}
		else
		{
			read_from_files(i, av, ac, flags);
			break;
		}
	if (flags->write_from_stdin == 0 && (flags->flag_p == 0 || flags->flag_q
		|| flags->flag_r))
		from_fd(flags, 0, NULL);
}

static void			ft_usage_error(char *cmd)
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
	exit(0);
}

static t_md5_stack	get_mode(char **argv)
{
	int i;

	i = 0;
	while (mode_change[i].name)
	{
		if (ft_strequ(argv[0], mode_change[i].name))
			break ;
		i++;
	}
	if (mode_change[i].name == NULL)
		ft_usage_error(argv[0]);
	return (mode_change[i]);
}

void			start_md5_processing(int ac, char **av, char read_from_fd)
{
	t_flags	*flags;
	t_md5_stack	temp;

	temp = get_mode(av);
	flags = (t_flags *)malloc(sizeof(t_flags));
	flags->f = temp.f;
	flags->name = ft_strdup(temp.name);
	flags->flag_q = 0;
	flags->flag_r = 0;
	flags->flag_p = 0;
	flags->write_from_stdin = 0;
	flags->read_from_fd = read_from_fd;
	parce_args(flags, av, ac);
	ft_strdel(&flags->name);
	free(flags);
}
