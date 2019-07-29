#include "unknow_project.h"

t_vector3_list create_t_vector3_list()
{
	t_vector3_list list;

	if (!(list.vector = (t_vector3 *)malloc(sizeof(t_vector3) * PUSH_SIZE)))
		error_exit(-18, "Can't malloc a t_vector3 array");
	list.size = 0;
	list.max_size = PUSH_SIZE;
	return (list);
}

t_vector3_list *initialize_t_vector3_list()
{
	t_vector3_list *list;

	if (!(list = (t_vector3_list *)malloc(sizeof(t_vector3_list))))
		error_exit(-19, "Can't create a t_vector3_list array");

	*list = create_t_vector3_list();

	return (list);
}

void	t_vector3_list_push_back(t_vector3_list *dest, t_vector3 to_add)
{
	t_vector3 *tmp;
	int i;

	if ((dest->size + 1) >= dest->max_size)
	{
		tmp = dest->vector;
		if (!(dest->vector = (t_vector3 *)malloc(sizeof(t_vector3) * (dest->size + 1 + PUSH_SIZE))))
			error_exit(-20, "Can't realloc a t_vector3 array");
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

void	t_vector3_list_add_back(t_vector3_list *dest, t_vector3 *to_add)
{
	t_vector3 *tmp;
	int i;

	if ((dest->size + 1) >= dest->max_size)
	{
		tmp = dest->vector;
		if (!(dest->vector = (t_vector3 *)malloc(sizeof(t_vector3) * (dest->size + 1 + PUSH_SIZE))))
			error_exit(-20, "Can't realloc a t_vector3 array");
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
	(dest->size)++;
}

void	free_t_vector3_list(t_vector3_list dest)
{
	free(dest.vector);
}

void	delete_t_vector3_list(t_vector3_list *dest)
{
	free_t_vector3_list(*dest);
	free(dest);
}

void	clean_t_vector3_list(t_vector3_list *dest)
{
	dest->size = 0;
}

t_vector3	t_vector3_list_at(t_vector3_list *dest, int index)
{
	if (index < 0 || index >= dest->size)
		error_exit(-24, "Segfault : t_vector3_list out of range");
	return (dest->vector[index]);
}

t_vector3	*t_vector3_list_get(t_vector3_list *dest, int index)
{
	if (index < 0 || index >= dest->size)
		error_exit(-24, "Segfault : t_vector3_list out of range");
	return (&dest->vector[index]);
}

float			*t_vector3_list_obtain(t_vector3_list *dest, int index)
{
	if (index < 0 || index >= dest->size)
		error_exit(-24, "Segfault : t_vector3_list out of range");
	return (&dest->value[index * 3]);
}

void			t_vector3_list_resize(t_vector3_list *dest, int new_size)
{
	t_vector3 *tmp;
	int i;
	int old_size;

	old_size = dest->size;
	tmp = dest->vector;
	if (!(dest->vector = (t_vector3 *)malloc(sizeof(t_vector3) * (new_size))))
		error_exit(-20, "Can't realloc a t_vector3 array");
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

void		t_vector3_list_edit(t_vector3_list *dest, int index, t_vector3 p_vector)
{
	if (index < 0 || index >= dest->size)
		error_exit(-24, "Segfault : t_vector3_list out of range");

	dest->vector[index] = p_vector;
}

void		t_vector3_list_set(t_vector3_list *dest, int index, t_vector3 *p_vector)
{
	if (index < 0 || index >= dest->size)
		error_exit(-24, "Segfault : t_vector3_list out of range");

	dest->vector[index] = *p_vector;
}