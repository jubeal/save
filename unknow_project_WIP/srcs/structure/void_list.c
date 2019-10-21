#include "unknow_project.h"

t_void_list	create_t_void_list(void)
{
	t_void_list	list;

	if (!(list.data = (void **)malloc(sizeof(void *) * PUSH_SIZE)))
		error_exit(-15, "Can't malloc a void * array");
	// printf("malloc t_void_list.data\n");
	list.size = 0;
	list.max_size = PUSH_SIZE;
	return (list);
}

t_void_list	*initialize_t_void_list(void)
{
	t_void_list	*list;

	if (!(list = (t_void_list *)malloc(sizeof(t_void_list))))
		error_exit(-16, "Can't create a t_void_list array");
	// printf("malloc t_void_list\n");
	*list = create_t_void_list();
	return (list);
}

void		t_void_list_add_back(t_void_list *dest, int nb, ...)
{
	void	*to_add;
	int		i;
	va_list	params;

	va_start(params, nb);
	i = -1;
	while (++i < nb)
	{
		to_add = va_arg(params, void *);
		t_void_list_push_back(dest, to_add);
	}
	va_end(params);
}

void		t_void_list_push_back(t_void_list *dest, void *to_add)
{
	void	**tmp;
	int		i;

	if ((dest->size + 1) >= dest->max_size)
	{
		tmp = dest->data;
		if (!(dest->data = (void **)malloc(sizeof(void *) \
							* (dest->size + 1 + PUSH_SIZE))))
			error_exit(-17, "Can't realloc a void * array");
		// printf("malloc t_void_list_push_back\n");
		i = -1;
		while (++i < dest->size)
			dest->data[i] = tmp[i];
		free(tmp);
		dest->max_size += PUSH_SIZE;
	}
	dest->data[dest->size] = to_add;
	dest->size++;
}

void		delete_t_void_list(t_void_list dest)
{
	free(dest.data);
	dest.data = NULL;
	dest.size = 0;
	// printf("delete t_void_list\n");
}

void		free_t_void_list(t_void_list *dest)
{
	delete_t_void_list(*dest);
	free(dest);
	// printf("free t_void_list\n");
}

void		clean_t_void_list(t_void_list *dest)
{
	dest->size = 0;
}

void		*t_void_list_at(t_void_list *dest, int index)
{
	if (index < 0 || index >= dest->size)
		error_exit(-23, "Segfault : t_void_list out of range");
	return (dest->data[index]);
}

void		**t_void_list_get(t_void_list *dest, int index)
{
	if (index < 0 || index >= dest->size)
		error_exit(-23, "Segfault : t_void_list out of range");
	return (&(dest->data[index]));
}
