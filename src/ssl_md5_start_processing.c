#include <fcntl.h>
#include "ft_ssl_md5.h"
#include <unistd.h>
#include <errno.h>


static t_flags	*create_flag(void (*f)(t_word *word, t_flags *flags),
	char *name)
{
	t_flags *flags;

	flags = (t_flags *)malloc(sizeof(t_flags));
	flags->f = f;
	flags->name = ft_strdup(name);
	flags->flag_q = 0;
	flags->flag_r = 0;
	flags->flag_p = 0;
	flags->write_from_stdin = 0;
	flags->flag_b = 0;
	flags->read_from_fd = 0;
	return (flags);
}

static int		print_error(t_md5_stack **head, char *name)
{
	t_md5_stack *temp;

	ft_printf("ft_ssl: Error: '%s' is an invalid command.\n\nStandart \
commands:\n\nMessage Digest commands:\n", name);
	temp = *head;
	while (temp->name != NULL)
	{
		ft_printf("%s\n", temp->name);
		temp = temp->next;
	}
	ft_printf("\nCipher commands:\n\n");
	while ((*head)->name != NULL)
	{
		temp = (*head)->next;
		ft_strdel(&((*head)->name));
		free(*head);
		*head = temp;
	}
	free(*head);
	return (0);
}

static void		read_from_files(int i, char **av, int ac, t_flags *flags)
{
	int fd;

	while (i < ac && ++flags->write_from_stdin)
	{
		fd = open(av[i], O_RDONLY);
		if (fd < 0 || read(fd, 0, 0) < 0)
			ft_printf("%s: %s: %s\n",
			ft_str_tolower(flags->name), av[i], strerror(errno));
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

void			start_md5_processing(int ac, char **av, char read_from_fd)
{
	t_flags	*flags;
	t_md5_stack	*head;
	t_md5_stack	*temp;

	head = make_md5_stack();
	temp = head;
	while (temp->name != NULL && ft_strcmp(av[0], temp->name))
		temp = temp->next;
	if (temp->name == NULL && !(print_error(&head, av[0])) && !read_from_fd)
		exit(0);
	if (temp->name == NULL)
	{
		// ssl_des_start_processing(ac, av);
		return ;
	}
	flags = create_flag(temp->f, temp->name);
	flags->read_from_fd = read_from_fd;
	while (head != NULL)
	{
		temp = head->next;
		ft_strdel(&head->name);
		free(head);
		head = temp;
	}
	parce_args(flags, av, ac);
	ft_strdel(&flags->name);
	free(flags);
}