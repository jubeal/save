#include "unknow_project.h"

t_vector2_list	create_t_vector2_list(void)
{
	t_vector2_list	list;

	if (!(list.vector = (t_vector2 *)malloc(sizeof(t_vector2) * PUSH_SIZE)))
		error_exit(-12, "Can't malloc a t_vector2 array");
	// printf("malloc t_vector2_list.vector\n");
	list.size = 0;
	list.max_size = PUSH_SIZE;
	return (list);
}

t_vector2_list	*initialize_t_vector2_list(void)
{
	t_vector2_list	*list;

	if (!(list = (t_vector2_list *)malloc(sizeof(t_vector2_list))))
		error_exit(-13, "Can't create a t_vector2_list array");
	// printf("malloc t_vector2_list\n");
	*list = create_t_vector2_list();
	return (list);
}

void			t_vector2_list_push_back(t_vector2_list *dest, t_vector2 to_add)
{
	t_vector2		*tmp;
	int				i;

	if ((dest->size + 1) >= dest->max_size)
	{
		tmp = dest->vector;
		if (!(dest->vector = (t_vector2 *)malloc(sizeof(t_vector2) \
									* (dest->size + 1 + PUSH_SIZE))))
			error_exit(-14, "Can't realloc a t_vector2 array");
		// printf("malloc t_vector2_list_push_back\n");
		i = -1;
		while (++i < dest->size)
			dest->vector[i] = tmp[i];
		free(tmp);
		dest->max_size += PUSH_SIZE;
	}
	dest->vector[dest->size] = to_add;
	dest->size++;
}

void			t_vector2_list_add_back(t_vector2_list *dest, t_vector2 *to_add)
{
	t_vector2	*tmp;
	int			i;

	if ((dest->size + 1) >= dest->max_size)
	{
		tmp = dest->vector;
		if (!(dest->vector = (t_vector2 *)malloc(sizeof(t_vector2) \
									* (dest->size + 1 + PUSH_SIZE))))
			error_exit(-20, "Can't realloc a t_vector2 array");
		// printf("malloc t_vector2_list_add_back\n");
		i = -1;
		while (++i < dest->size)
			dest->vector[i] = tmp[i];
		free(tmp);
		dest->max_size += PUSH_SIZE;
	}
	dest->vector[dest->size].x = to_add->x;
	dest->vector[dest->size].y = to_add->y;
	dest->size++;
}

void			delete_t_vector2_list(t_vector2_list dest)
{
	free(dest.vector);
	// printf("delete t_vector2_list\n");
}

void			free_t_vector2_list(t_vector2_list *dest)
{
	delete_t_vector2_list(*dest);
	free(dest);
	// printf("free t_vector2_list\n");
}

void			clean_t_vector2_list(t_vector2_list *dest)
{
	dest->size = 0;
}

t_vector2		t_vector2_list_at(t_vector2_list *dest, int index)
{
	if (index < 0 || index >= dest->size)
		error_exit(-22, "Segfault : t_vector2_list out of range");
	return (dest->vector[index]);
}

t_vector2		*t_vector2_list_get(t_vector2_list *dest, int index)
{
	if (index < 0 || index >= dest->size)
		error_exit(-22, "Segfault : t_vector2_list out of range");
	return (&dest->vector[index]);
}

float			*t_vector2_list_obtain(t_vector2_list *dest, int index)
{
	if (index < 0 || index >= dest->size)
		error_exit(-22, "Segfault : t_vector2_list out of range");
	return (&dest->value[index * 2]);
}

void			t_vector2_list_resize(t_vector2_list *dest, int new_size)
{
	t_vector2	*tmp;
	int			i;
	int			old_size;

	old_size = dest->size;
	tmp = dest->vector;
	if (!(dest->vector = (t_vector2 *)malloc(sizeof(t_vector2) * (new_size))))
		error_exit(-20, "Can't realloc a t_vector2 array");
	// printf("malloc t_vector2_list_resize\n");
	i = 0;
	while (i < dest->size && i < new_size && i < old_size)
	{
		dest->vector[i] = tmp[i];
		i++;
	}
	if (old_size != 0)
		free(tmp);
	dest->max_size = new_size;
	dest->size = i;
}

void			t_vector2_list_edit(t_vector2_list *dest, int index, t_vector2 p_vector)
{
	if (index < 0 || index >= dest->size)
		error_exit(-22, "Segfault : t_vector2_list out of range");
	dest->vector[index] = p_vector;
}

void			t_vector2_list_set(t_vector2_list *dest, int index, t_vector2 *p_vector)
{
	if (index < 0 || index >= dest->size)
		error_exit(-22, "Segfault : t_vector2_list out of range");
	dest->vector[index] = *p_vector;
}
