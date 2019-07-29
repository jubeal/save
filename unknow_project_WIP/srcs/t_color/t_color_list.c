#include "unknow_project.h"

t_color_list create_t_color_list()
{
	t_color_list list;

	if (!(list.color = (t_color *)malloc(sizeof(t_color) * PUSH_SIZE)))
		error_exit(-25, "Can't malloc a t_color array");
	list.size = 0;
	list.max_size = PUSH_SIZE;
	return (list);
}

t_color_list *initialize_t_color_list()
{
	t_color_list *list;

	if (!(list = (t_color_list *)malloc(sizeof(t_color_list))))
		error_exit(-26, "Can't create a t_color_list array");

	*list = create_t_color_list();

	return (list);
}

void	t_color_list_push_back(t_color_list *dest, t_color to_add)
{
	t_color *tmp;
	int i;

	if ((dest->size + 1) >= dest->max_size)
	{
		tmp = dest->color;
		if (!(dest->color = (t_color *)malloc(sizeof(t_color) * (dest->size + 1 + PUSH_SIZE))))
			error_exit(-27, "Can't realloc a t_color array");
		i = 0;
		while (i < dest->size)
		{
			dest->color[i] = tmp[i];
			i++;
		}
		free(tmp);
		dest->max_size += PUSH_SIZE;
	}
	dest->color[dest->size] = to_add;
	dest->size++;
}

void	t_color_list_add_back(t_color_list *dest, t_color *to_add)
{
	t_color *tmp;
	int i;

	if ((dest->size + 1) >= dest->max_size)
	{
		tmp = dest->color;
		if (!(dest->color = (t_color *)malloc(sizeof(t_color) * (dest->size + 1 + PUSH_SIZE))))
			error_exit(-20, "Can't realloc a t_color array");
		i = 0;
		while (i < dest->size)
		{
			dest->color[i] = tmp[i];
			i++;
		}
		free(tmp);
		dest->max_size += PUSH_SIZE;
	}
	dest->color[dest->size].r = to_add->r;
	dest->color[dest->size].g = to_add->g;
	dest->color[dest->size].b = to_add->b;
	dest->color[dest->size].a = to_add->a;
	(dest->size)++;
}

void	free_t_color_list(t_color_list dest)
{
	free(dest.color);
}

void	delete_t_color_list(t_color_list *dest)
{
	free_t_color_list(*dest);
	free(dest);
}

void	clean_t_color_list(t_color_list *dest)
{
	dest->size = 0;
}

t_color	t_color_list_at(t_color_list *dest, int index)
{
	if (index < 0 || index >= dest->size)
		error_exit(-28, "Segfault : t_color_list out of range");
	return (dest->color[index]);
}

t_color	*t_color_list_get(t_color_list *dest, int index)
{
	if (index < 0 || index >= dest->size)
		error_exit(-28, "Segfault : t_color_list out of range");
	return (&dest->color[index]);
}

float	*t_color_list_obtain(t_color_list *dest, int index)
{
	if (index < 0 || index >= dest->size)
		error_exit(-28, "Segfault : t_color_list out of range");
	return (&dest->value[index * 2]);
}

void			t_color_list_resize(t_color_list *dest, int new_size)
{
	t_color *tmp;
	int i;
	int old_size;

	old_size = dest->size;
	tmp = dest->color;
	if (!(dest->color = (t_color *)malloc(sizeof(t_color) * (new_size))))
		error_exit(-20, "Can't realloc a t_color array");
	i = 0;
	while (i < dest->size && i < new_size && i < old_size)
	{
		dest->color[i] = tmp[i];
		i++;
	}
	if (old_size != 0)
		free(tmp);
	dest->max_size = new_size;
	dest->size = i;
}

void		t_color_list_edit(t_color_list *dest, int index, t_color p_color)
{
	if (index < 0 || index >= dest->size)
		error_exit(-28, "Segfault : t_color_list out of range");

	dest->color[index] = p_color;
}

void		t_color_list_set(t_color_list *dest, int index, t_color *p_color)
{
	if (index < 0 || index >= dest->size)
		error_exit(-28, "Segfault : t_color_list out of range in t_color_list_set");

	dest->color[index] = *p_color;
}
