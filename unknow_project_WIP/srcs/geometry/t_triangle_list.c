#include "unknow_project.h"

t_triangle_list create_t_triangle_list()
{
	t_triangle_list list;

	if (!(list.triangle = (t_triangle *)malloc(sizeof(t_triangle) * PUSH_SIZE)))
		error_exit(-32, "Can't malloc a t_triangle array");
	list.size = 0;
	list.max_size = PUSH_SIZE;
	return (list);
}

t_triangle_list *initialize_t_triangle_list()
{
	t_triangle_list *list;

	if (!(list = (t_triangle_list *)malloc(sizeof(t_triangle_list))))
		error_exit(-33, "Can't create a t_triangle_list array");

	*list = create_t_triangle_list();

	return (list);
}

void	t_triangle_list_push_back(t_triangle_list *dest, t_triangle to_add)
{
	t_triangle *tmp;
	int i;

	if ((dest->size + 1) >= dest->max_size)
	{
		tmp = dest->triangle;
		if (!(dest->triangle = (t_triangle *)malloc(sizeof(t_triangle) * (dest->size + 1 + PUSH_SIZE))))
			error_exit(-34, "Can't realloc a t_triangle array");
		i = 0;
		while (i < dest->size)
		{
			dest->triangle[i] = tmp[i];
			i++;
		}
		free(tmp);
		dest->max_size += PUSH_SIZE;
	}
	dest->triangle[dest->size] = to_add;
	dest->size++;
}

void	t_triangle_list_add_back(t_triangle_list *dest, t_triangle *to_add)
{
	t_triangle *tmp;
	int i;

	if ((dest->size + 1) >= dest->max_size)
	{
		tmp = dest->triangle;
		if (!(dest->triangle = (t_triangle *)malloc(sizeof(t_triangle) * (dest->size + 1 + PUSH_SIZE))))
			error_exit(-35, "Can't realloc a t_triangle array");
		i = 0;
		while (i < dest->size)
		{
			dest->triangle[i] = tmp[i];
			i++;
		}
		free(tmp);
		dest->max_size += PUSH_SIZE;
	}
	dest->triangle[dest->size].a = to_add->a;
	dest->triangle[dest->size].b = to_add->b;
	dest->triangle[dest->size].c = to_add->c;
	dest->size++;
}

void	free_t_triangle_list(t_triangle_list dest)
{
	free(dest.triangle);
}

void	delete_t_triangle_list(t_triangle_list *dest)
{
	free_t_triangle_list(*dest);
	free(dest);
}

void	clean_t_triangle_list(t_triangle_list *dest)
{
	dest->size = 0;
}

t_triangle	t_triangle_list_at(t_triangle_list *dest, int index)
{
	if (index < 0 || index >= dest->size)
		error_exit(-36, "Segfault : t_triangle_list out of range");
	return (dest->triangle[index]);
}

t_triangle	*t_triangle_list_get(t_triangle_list *dest, int index)
{
	if (index < 0 || index >= dest->size)
		error_exit(-36, "Segfault : t_triangle_list out of range");
	return (&dest->triangle[index]);
}

void			t_triangle_list_resize(t_triangle_list *dest, int new_size)
{
	t_triangle *tmp;
	int i;
	int old_size;

	old_size = dest->size;

	tmp = dest->triangle;
	if (!(dest->triangle = (t_triangle *)malloc(sizeof(t_triangle) * (new_size))))
		error_exit(-35, "Can't realloc a t_triangle array");
	i = 0;
	while (i < dest->size && i < new_size && i < old_size)
	{
		dest->triangle[i] = tmp[i];
		i++;
	}
	if (old_size != 0)
		free(tmp);
	dest->max_size = new_size;
	dest->size = i;
}
