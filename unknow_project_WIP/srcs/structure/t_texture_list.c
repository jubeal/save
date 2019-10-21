#include "unknow_project.h"

t_texture_list	create_t_texture_list(void)
{
	t_texture_list	list;

	if (!(list.texture = (t_texture *)malloc(sizeof(t_texture) * PUSH_SIZE)))
		error_exit(-25, "Can't malloc a t_texture array");
	// printf("malloc t_texture_list.texture\n");
	list.size = 0;
	list.max_size = PUSH_SIZE;
	return (list);
}

t_texture_list	*initialize_t_texture_list(void)
{
	t_texture_list	*list;

	if (!(list = (t_texture_list *)malloc(sizeof(t_texture_list))))
		error_exit(-26, "Can't create a t_texture_list array");
	// printf("malloc t_texture_list\n");
	*list = create_t_texture_list();
	return (list);
}

void			t_texture_list_push_back(t_texture_list *dest, t_texture to_add)
{
	t_texture	*tmp;
	int			i;

	if ((dest->size + 1) >= dest->max_size)
	{
		tmp = dest->texture;
		if (!(dest->texture = (t_texture *)malloc(sizeof(t_texture) \
									* (dest->size + 1 + PUSH_SIZE))))
			error_exit(-27, "Can't realloc a t_texture array");
		// printf("malloc t_texture_list_push_back\n");
		i = -1;
		while (++i < dest->size)
			dest->texture[i] = tmp[i];
		free(tmp);
		dest->max_size += PUSH_SIZE;
	}
	dest->texture[dest->size] = to_add;
	dest->size++;
}

void			t_texture_list_add_back(t_texture_list *dest, t_texture *to_add)
{
	t_texture	*tmp;
	int			i;

	if ((dest->size + 1) >= dest->max_size)
	{
		tmp = dest->texture;
		if (!(dest->texture = (t_texture *)malloc(sizeof(t_texture) \
									* (dest->size + 1 + PUSH_SIZE))))
			error_exit(-20, "Can't realloc a t_texture array");
		// printf("malloc t_texture_list_add_back\n");
		i = -1;
		while (++i < dest->size)
			dest->texture[i] = tmp[i];
		free(tmp);
		dest->max_size += PUSH_SIZE;
	}
	dest->texture[dest->size].surface = to_add->surface;
	dest->texture[dest->size].id = to_add->id;
	(dest->size)++;
}

void			delete_t_texture_list(t_texture_list dest)
{
	free(dest.texture);
	// printf("delete t_texture_list\n");
}

void			free_t_texture_list(t_texture_list *dest)
{
	delete_t_texture_list(*dest);
	free(dest);
	// printf("free t_texture_list\n");
}

void			clean_t_texture_list(t_texture_list *dest)
{
	dest->size = 0;
}

t_texture		t_texture_list_at(t_texture_list *dest, int index)
{
	if (index < 0 || index >= dest->size)
		error_exit(-28, "Segfault : t_texture_list out of range");
	return (dest->texture[index]);
}

t_texture		*t_texture_list_get(t_texture_list *dest, int index)
{
	if (index < 0 || index >= dest->size)
		error_exit(-28, "Segfault : t_texture_list out of range");
	return (&dest->texture[index]);
}
