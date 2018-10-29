#include "ft_ssl_md5.h"
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

static void	make_word(t_word *res, unsigned char *word, size_t length)
{
	res->word = word;
	res->length = length * 8;
}

static void s_flag_has_arg(t_flags *flags, char **av, int *i, int *j, t_word *word)
{
	if (!flags->flag_q && !flags->flag_r)
			ft_printf("%s (\"%s\") = ", ft_strto(flags->name, 1),
				&av[*i][*j + 1]);
	make_word(word, (unsigned char *)&av[*i][*j + 1], ft_strlen(&av[*i][*j + 1]));
	flags->f(word);
	if (!flags->flag_q && flags->flag_r)
		ft_printf(" \"%s\"", &av[*i][*j + 1]);
	*j = *j + (int)ft_strlen(&av[*i][*j + 1]);
}

static void		parce_s_flag(t_flags *flags, char **av, int *i, int *j)
{
	t_word *word;

	word = (t_word *)malloc(sizeof(t_word));
	if (av[*i][*j + 1])
		s_flag_has_arg(flags, av, i, j, word);
	// {
	// 	if (!flags->flag_q && !flags->flag_r)
	// 		ft_printf("%s (\"%s\") = ", ft_strto(flags->name, 1),
	else
	{
		make_word(word, (unsigned char *)av[++(*i)], ft_strlen(av[*i]));
		if (!flags->flag_q && !flags->flag_r)
			ft_printf("%s (\"%s\") = ", ft_strto(flags->name, 1), av[*i]);
		flags->f(word);
		if (!flags->flag_q && flags->flag_r)
			ft_printf(" \"%s\"", av[*i]);
		(*j) = (int)ft_strlen(av[*i]) - 1;
	}
	free(word);
	ft_printf("\n");
}

// static void		parce_s_flag(t_flags *flags, char **av, int *i, int *j)
// {
// 	t_word *word;

// 	if (av[*i][*j + 1])
// 	{
// 		if (!flags->flag_q && !flags->flag_r)
// 			ft_printf("%s (\"%s\") = ", ft_strto(flags->name, 1),
// 				&av[*i][*j + 1]);
// 		word = make_word((unsigned char *)&av[*i][*j + 1], ft_strlen(&av[*i][*j + 1]));
// 		flags->f(word);
// 		if (!flags->flag_q && flags->flag_r)
// 			ft_printf(" \"%s\"", &av[*i][*j + 1]);
// 		*j = *j + (int)ft_strlen(&av[*i][*j + 1]);
// 	}
// 	else
// 	{
// 		word = make_word((unsigned char *)av[++(*i)], ft_strlen(av[*i]));
// 		if (!flags->flag_q && !flags->flag_r)
// 			ft_printf("%s (\"%s\") = ", ft_strto(flags->name, 1), av[*i]);
// 		flags->f(word);
// 		if (!flags->flag_q && flags->flag_r)
// 			ft_printf(" \"%s\"", av[*i]);
// 		(*j) = (int)ft_strlen(av[*i]) - 1;
// 	}
// 	free(word);
// 	ft_printf("\n");
// }

static void			parse_fd_nul(t_flags *flags)
{
	unsigned char	*line;
	t_word	*word;

	if (flags->flag_p > 1)
	{
		word = (t_word *)malloc(sizeof(t_word));
		word->word = (unsigned char *)"";
		word->length = 0;
		flags->f(word);
		ft_printf("\n");
		free(word);
		return ;
	}
	line = ft_str_unsigned_new(0);
	word = msg_from_fd(0, &line);
	if (flags->flag_p)
		ft_printf("%s", line);
	flags->f(word);
	ft_printf("\n");
	free(word);
	ft_str_unsigned_del(&line);
}

static void			parse_fd(t_flags *flags, int fd, char *name)
{
	unsigned char	*line;
	t_word	*word;

	if (!flags->flag_r && !flags->flag_q)
			ft_printf("%s (%s) = ", ft_strto(flags->name, 1), name);
	line = ft_str_unsigned_new(0);
	word = msg_from_fd(fd, &line);
	flags->f(word);
	if (flags->flag_r && !flags->flag_q)
		ft_printf(" %s", name);
	ft_printf("\n");
	free(word);
	ft_str_unsigned_del(&line);
}

static void				parce_flags(t_flags *flags, char **av, int ac, int *i)
{
	int j;

	j = 0;
	while (++j && av[*i][j])
	{
		if (!(ft_strchr("pqrs", av[*i][j])))
				ft_flag_error(flags, av[*i][j], 0);
		if (av[*i][j] == 'q')
			flags->flag_q = 1;
		if (av[*i][j] == 'r')
			flags->flag_r = 1;
		if (av[*i][j] == 'p' && ++flags->flag_p)
			parse_fd_nul(flags);
		if (av[*i][j] == 's')
		{
			flags->write_from_stdin = 1;
			if (*i == ac - 1 && !av[*i][j + 1])
				ft_flag_error(flags, av[*i][j], 1);
			else
				parce_s_flag(flags, av, i, &j);
		}
	}
}

void		parce_args(t_flags *flags, char **av, int ac)
{
	int i;
	int fd;

	i = 0;
	while (++i < ac)
		if (av[i][0] == '-' && av[i][1])
			parce_flags(flags, av, ac, &i);
		else
		{
			while (i < ac && ++flags->write_from_stdin)
			{
				fd = open(av[i], O_RDONLY);
				if (fd < 0 || read(fd, 0, 0) < 0)
					ft_printf("%s: %s: %s\n", ft_strto(flags->name, 0), av[i], strerror(errno));
				else
					parse_fd(flags, fd, av[i]);
				i++;
				close(fd);
			}
			break;
		}
	if (flags->write_from_stdin == 0 && (flags->flag_p == 0 || flags->flag_q
		|| flags->flag_r))
		parse_fd_nul(flags);
}
