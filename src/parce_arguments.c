#include "ft_ssl_md5.h"

static t_word	*make_word(unsigned char *word, size_t length)
{
	t_word	*res;

	res = (t_word *)malloc(sizeof(t_word));
	res->word = word;
	res->length = length * 8;
	return (res);
}

static void		parce_s_flag(t_flags *flags, char **av, int *i, int *j)
{
	t_word *word;

	if (av[*i][*j + 1])
	{
		if (!flags->flag_q && !flags->flag_r)
			ft_printf("%s (\"%s\") = ", ft_str_to_upper(flags->name),
				&av[*i][*j + 1]);
		word = make_word((unsigned char *)&av[*i][*j + 1], ft_strlen(&av[*i][*j + 1]));
		flags->f(word, flags);
		if (!flags->flag_q && flags->flag_r)
			ft_printf(" \"%s\"", &av[*i][*j + 1]);
		*j = *j + (int)ft_strlen(&av[*i][*j + 1]);
	}
	else
	{
		word = make_word((unsigned char *)av[++(*i)], ft_strlen(av[*i]));
		if (!flags->flag_q && !flags->flag_r)
			ft_printf("%s (\"%s\") = ", ft_str_to_upper(flags->name), av[*i]);
		flags->f(word, flags);
		if (!flags->flag_q && flags->flag_r)
			ft_printf(" \"%s\"", av[*i]);
		(*j) = (int)ft_strlen(av[*i]) - 1;
	}
	free(word);
	ft_printf("\n");
}

void			from_fd(t_flags *flags, int fd, char *name)
{
	unsigned char	*line;
	size_t	length;
	t_word	*word;

	(fd != 0 && !flags->flag_r && !flags->flag_q) ?
			ft_printf("%s (%s) = ", ft_str_to_upper(flags->name), name) : 0;
	if (fd == 0 && flags->flag_p > 1)
	{
		word = make_word((unsigned char *)"", 0);
		flags->f(word, flags);
		ft_printf("\n");
		free(word);
		return ;
	}
	line = ft_str_unsigned_new(0);
	length = read_from_fd(fd, &line);
	(fd == 0 && flags->flag_p) ? (ft_printf("%s", line)) : 0;
	word = make_word(line, length);
	flags->f(word, flags);
	(fd != 0 && flags->flag_r && !flags->flag_q) ? ft_printf(" %s", name) : 0;
	ft_printf("\n");
	free(word);
	ft_str_unsigned_del(&line);
}

int				parce_flags(t_flags *flags, char **av, int ac, int *i)
{
	int j;

	j = 0;
	while (++j && av[*i][j])
	{
		if (av[*i][j] != 's' && av[*i][j] != 'q' &&
			av[*i][j] != 'r' && av[*i][j] != 'p' && av[*i][j] != 'b')
		{
			ft_printf("%s: illegal option -- %c\nAvailable flags:\n-p: echo STD\
IN to STDOUT and append cheksum to STDOUT\n-q: quiet mode\n-r: reverse format\n\
-s: print the sum of a string\n-b: print in binary\n", flags->name, av[*i][j]);
			if (!flags->read_from_fd)
				return (-1);
			else
				return (-2);
		}
		(av[*i][j] == 'q') ? flags->flag_q = 1 : 0;
		(av[*i][j] == 'r') ? flags->flag_r = 1 : 0;
		(av[*i][j] == 'b') ? flags->flag_b = 1 : 0;
		(av[*i][j] == 'p' && ++flags->flag_p) ? from_fd(flags, 0, NULL) : 0;
		if (av[*i][j] == 's' && (flags->write_from_stdin = 1))
			(*i == ac - 1 && !av[*i][j + 1]) ? (ft_printf("%s: option requires \
an argument -- s\n", flags->name)) : parce_s_flag(flags, av, i, &j);
	}
	return (0);
}
