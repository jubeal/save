#include "unknow_project.h"

t_mesh_list	create_t_mesh_list(void)
{
	t_mesh_list	list;

	if (!(list.mesh = (t_mesh *)malloc(sizeof(t_mesh) * PUSH_SIZE)))
		error_exit(-18, "Can't malloc a t_mesh array");
	// printf("malloc t_mesh_list.mesh\n");
	list.size = 0;
	list.max_size = PUSH_SIZE;
	return (list);
}

t_mesh_list	*initialize_t_mesh_list(void)
{
	t_mesh_list	*list;

	if (!(list = (t_mesh_list *)malloc(sizeof(t_mesh_list))))
		error_exit(-19, "Can't create a t_mesh_list array");
	// printf("malloc t_mesh_list\n");
	*list = create_t_mesh_list();
	return (list);
}

void		t_mesh_list_push_back(t_mesh_list *dest, t_mesh to_add)
{
	t_mesh	*tmp;
	int		i;

	if ((dest->size + 1) >= dest->max_size)
	{
		tmp = dest->mesh;
		if (!(dest->mesh = (t_mesh *)malloc(sizeof(t_mesh) \
											* (dest->size + 1 + PUSH_SIZE))))
			error_exit(-20, "Can't realloc a t_mesh array");
		// printf("malloc t_mesh_list_push_back\n");
		i = -1;
		while (++i < dest->size)
			dest->mesh[i] = tmp[i];
		free(tmp);
		dest->max_size += PUSH_SIZE;
	}
	dest->mesh[dest->size] = to_add;
	(dest->size)++;
}

void		t_mesh_list_erase(t_mesh_list *dest, int index)
{
	delete_t_mesh(*t_mesh_list_get(dest, index));
	while (index < dest->size)
	{
		dest[index + 1] = dest[index];
		index++;
	}
}

void		delete_t_mesh_list(t_mesh_list dest)
{
	free(dest.mesh);
	// printf("delete t_mesh_list\n");
}

void		free_t_mesh_list(t_mesh_list *dest)
{
	delete_t_mesh_list(*dest);
	free(dest);
	// printf("free t_mesh_list\n");
}

void		clean_t_mesh_list(t_mesh_list *dest)
{
	dest->size = 0;
}

t_mesh		t_mesh_list_at(t_mesh_list *dest, int index)
{
	if (index < 0 || index >= dest->size)
		error_exit(-24, "Segfault : t_mesh_list out of range");
	return (dest->mesh[index]);
}

t_mesh		*t_mesh_list_get(t_mesh_list *dest, int index)
{
	if (index < 0 || index >= dest->size)
		error_exit(-24, "Segfault : t_mesh_list out of range");
	return (&(dest->mesh[index]));
}

int			t_mesh_list_get_index(t_mesh_list *dest, t_mesh *mesh)
{
	int		i;

	i = -1;
	while (++i < dest->size)
	{
		if (dest[i].mesh == mesh)
			return (i);
	}
	return (-1);
}
