#include "unknow_project.h"

t_vector4_list create_t_vector4_list()
{
	t_vector4_list list;

	if (!(list.vector = (t_vector4 *)malloc(sizeof(t_vector4) * PUSH_SIZE)))
		error_exit(-18, "Can't malloc a t_vector4 array");
	list.size = 0;
	list.max_size = PUSH_SIZE;
	return (list);
}

t_vector4_list *initialize_t_vector4_list()
{
	t_vector4_list *list;

	if (!(list = (t_vector4_list *)malloc(sizeof(t_vector4_list))))
		error_exit(-19, "Can't create a t_vector4_list array");

	*list = create_t_vector4_list();

	return (list);
}

void	t_vector4_list_push_back(t_vector4_list *dest, t_vector4 to_add)
{
	t_vector4 *tmp;
	int i;

	if ((dest->size + 1) >= dest->max_size)
	{
		tmp = dest->vector;
		if (!(dest->vector = (t_vector4 *)malloc(sizeof(t_vector4) * (dest->size + 1 + PUSH_SIZE))))
			error_exit(-20, "Can't realloc a t_vector4 array");
		i = 0;
		while (i < dest->size)
		{
			dest->vector[i] = tmp[i];
			i++;
		}
		free(tmp);
		dest->max_size += PUSH_SIZE;
	}
	dest->vector[dest->size] = to_add;
	(dest->size)++;
}

void	t_vector4_list_add_back(t_vector4_list *dest, t_vector4 *to_add)
{
	t_vector4 *tmp;
	int i;

	if ((dest->size + 1) >= dest->max_size)
	{
		tmp = dest->vector;
		if (!(dest->vector = (t_vector4 *)malloc(sizeof(t_vector4) * (dest->size + 1 + PUSH_SIZE))))
			error_exit(-20, "Can't realloc a t_vector4 array");
		i = 0;
		while (i < dest->size)
		{
			dest->vector[i] = tmp[i];
			i++;
		}
		free(tmp);
		dest->max_size += PUSH_SIZE;
	}
	dest->vector[dest->size].x = to_add->x;
	dest->vector[dest->size].y = to_add->y;
	dest->vector[dest->size].z = to_add->z;
	dest->vector[dest->size].w = to_add->w;
	(dest->size)++;
}

void	delete_t_vector4_list(t_vector4_list dest)
{
	free(dest.vector);
	dest.vector = NULL;
	dest.size = 0;
}

void	free_t_vector4_list(t_vector4_list *dest)
{
	delete_t_vector4_list(*dest);
	free(dest);
}

void	clean_t_vector4_list(t_vector4_list *dest)
{
	dest->size = 0;
}

t_vector4	t_vector4_list_at(t_vector4_list *dest, int index)
{
	if (index < 0 || index >= dest->size)
		error_exit(-24, "Segfault : t_vector4_list out of range");
	return (dest->vector[index]);
}

t_vector4	*t_vector4_list_get(t_vector4_list *dest, int index)
{
	if (index < 0 || index >= dest->size)
		error_exit(-24, "Segfault : t_vector4_list out of range");
	return (&dest->vector[index]);
}

float			*t_vector4_list_obtain(t_vector4_list *dest, int index)
{
	if (index < 0 || index >= dest->size)
		error_exit(-24, "Segfault : t_vector4_list out of range");
	return (&dest->value[index * 3]);
}

void			t_vector4_list_resize(t_vector4_list *dest, int new_size)
{
	t_vector4 *tmp;
	int i;
	int old_size;

	old_size = dest->size;
	tmp = dest->vector;
	if (!(dest->vector = (t_vector4 *)malloc(sizeof(t_vector4) * (new_size))))
		error_exit(-20, "Can't realloc a t_vector4 array");
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

void		t_vector4_list_edit(t_vector4_list *dest, int index, t_vector4 p_vector)
{
	if (index < 0 || index >= dest->size)
		error_exit(-24, "Segfault : t_vector4_list out of range");

	dest->vector[index] = p_vector;
}

void		t_vector4_list_set(t_vector4_list *dest, int index, t_vector4 *p_vector)
{
	if (index < 0 || index >= dest->size)
		error_exit(-24, "Segfault : t_vector4_list out of range");

	dest->vector[index] = *p_vector;
}
