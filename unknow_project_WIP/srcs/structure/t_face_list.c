#include "unknow_project.h"

t_face_list	create_t_face_list(void)
{
	t_face_list	list;

	if (!(list.face = (t_face *)malloc(sizeof(t_face) * PUSH_SIZE)))
		error_exit(-25, "Can't malloc a t_face array");
	list.size = 0;
	list.max_size = PUSH_SIZE;
	return (list);
}

t_face_list	*initialize_t_face_list(void)
{
	t_face_list	*list;

	if (!(list = (t_face_list *)malloc(sizeof(t_face_list))))
		error_exit(-26, "Can't create a t_face_list array");
	*list = create_t_face_list();
	return (list);
}

void		t_face_list_push_back(t_face_list *dest, t_face to_add)
{
	t_face	*tmp;
	int		i;

	if ((dest->size + 1) >= dest->max_size)
	{
		tmp = dest->face;
		if (!(dest->face = (t_face *)malloc(sizeof(t_face) \
							* (dest->size + 1 + PUSH_SIZE))))
			error_exit(-27, "Can't realloc a t_face array");
		i = -1;
		while (++i < dest->size)
			dest->face[i] = tmp[i];
		free(tmp);
		dest->max_size += PUSH_SIZE;
	}
	dest->face[dest->size] = to_add;
	dest->size++;
}

void		t_face_list_add_back(t_face_list *dest, t_face *to_add)
{
	t_face	*tmp;
	int		i;

	if ((dest->size + 1) >= dest->max_size)
	{
		tmp = dest->face;
		if (!(dest->face = (t_face *)malloc(sizeof(t_face) \
							* (dest->size + 1 + PUSH_SIZE))))
			error_exit(-20, "Can't realloc a t_face array");
		i = -1;
		while (++i < dest->size)
			dest->face[i] = tmp[i];
		free(tmp);
		dest->max_size += PUSH_SIZE;
	}
	dest->face[dest->size].index_vertices[0] = to_add->index_vertices[0];
	dest->face[dest->size].index_vertices[1] = to_add->index_vertices[1];
	dest->face[dest->size].index_vertices[2] = to_add->index_vertices[2];
	dest->face[dest->size].index_uvs[0] = to_add->index_uvs[0];
	dest->face[dest->size].index_uvs[1] = to_add->index_uvs[1];
	dest->face[dest->size].index_uvs[2] = to_add->index_uvs[2];
	dest->face[dest->size].normale = to_add->normale;
	(dest->size)++;
}

void		delete_t_face_list(t_face_list dest)
{
	free(dest.face);
}

void		free_t_face_list(t_face_list *dest)
{
	delete_t_face_list(*dest);
	free(dest);
}

void		clean_t_face_list(t_face_list *dest)
{
	dest->size = 0;
}

t_face		t_face_list_at(t_face_list *dest, int index)
{
	if (index < 0 || index >= dest->size)
		error_exit(-28, "Segfault : t_face_list out of range");
	return (dest->face[index]);
}

t_face		*t_face_list_get(t_face_list *dest, int index)
{
	if (index < 0 || index >= dest->size)
		error_exit(-28, "Segfault : t_face_list out of range");
	return (&dest->face[index]);
}
