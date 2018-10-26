#include "ft_ssl_md5.h"

static void		push(t_md5_stack **head, char *name, 
				void (*f)(t_word *word, t_flags *flags))
{
	t_md5_stack *temp;

	temp = (t_md5_stack *)malloc(sizeof(t_md5_stack));
	temp->f = f;
	temp->name = ft_strdup(name);
	temp->next = *head;
	*head = temp;
}

t_md5_stack		*make_md5_stack(void)
{
	t_md5_stack *head;

	head = NULL;
	push(&head, NULL, NULL);
	push(&head, "md5", ssl_md5);
	push(&head, "sha224", ssl_sha224);
	push(&head, "sha256", ssl_sha256);
	push(&head, "sha384", ssl_sha384);
	push(&head, "sha512", ssl_sha512);
	return (head);
}
