#include "ft_ssl_md5.h"
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int			main(int ac, char **av)
{
	char	*line;
	char	**argv;
	int		argc;
	int		i;

	if (ac < 2)
	{
		ft_printf("ft_ssl>");
		while (get_next_line(0, &line))
		{
			if ((i = -1) && line && !ft_strcmp(line, "exit"))
				exit(0);
			(!(argc = 0) && line) ? argv = ft_strsplit(line, ' ') : 0;
			while (line && line[++i])
				if ((line[i] == ' ' && line[i + 1] != ' ' && line[i + 1])
					|| (i == 0 && line[i] != ' '))
					argc++;
			line[0] ? start_md5_processing(argc, argv, 1) : 0;
			ft_strdel(&line);
			ft_printf("ft_ssl>");
		}
	}
	else
		start_md5_processing(ac - 1, &av[1], 0);
	return (0);
}