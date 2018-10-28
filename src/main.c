#include "ft_ssl_md5.h"
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

void		stdin_read(void)
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
			start_md5_processing(argc, split, 1);
		ft_strdel(&line);
		ft_printf("ft_ssl> ");
	}
}

int			main(int ac, char **av)
{

	if (ac == 1)
		stdin_read();
	else
		start_md5_processing(ac - 1, &av[1], 0);
	return (0);
}
