#include "ft_ssl_md5.h"
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

static const t_ssl_mode		mode_change[] = {
	{ "md5", &md5},
	{"sha256", &sha256},
	{"sha224", &sha224},
	{"sha512", &sha512},
	{"sha384", &sha384},
	{ NULL, NULL}
};

static t_ssl_mode	get_mode(char **argv)
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
		ft_mode_error(argv[0]);
	return (mode_change[i]);
}

static void			start_ssl(int ac, char **av, char read_from_fd)
{
	t_flags	*flags;
	t_ssl_mode	temp;

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
	// system("leaks -q ft_ssl");
}

static void		one_arg(void)
{
	char 	*line;
	char	**split;
	int		argc;
	int		i;

	ft_printf("ft_ssl> ");
	while (get_next_line(0, &line))
	{
		i = -1;
		argc = 0;
		if (line && ft_strequ(line, "exit"))
			exit(0);
		if (line)
			split = ft_strsplit(line, ' ');
		while (line && line[++i])
			if ((line[i] == ' ' && line[i + 1] != ' ' && line[i + 1])
				|| (i == 0 && line[i] != ' '))
				argc++;
		if (line)
			start_ssl(argc, split, 1);
		ft_strdel(&line);
		ft_printf("ft_ssl> ");
	}
}

int			main(int argc, char **argv)
{

	if (argc == 1)
		one_arg();
	else
		start_ssl(argc - 1, &argv[1], 0);
	return (0);
}
