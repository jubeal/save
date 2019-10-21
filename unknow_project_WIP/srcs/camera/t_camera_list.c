#include "unknow_project.h"

t_camera_list	create_t_camera_list()
{
	t_camera_list	list;

	if (!(list.camera = (t_camera *)malloc(sizeof(t_camera) * PUSH_SIZE)))
		error_exit(-18, "Can't malloc a t_camera array");
	// printf("malloc t_camera_list.camera\n");
	list.size = 0;
	list.max_size = PUSH_SIZE;
	return (list);
}

t_camera_list	*initialize_t_camera_list()
{
	t_camera_list *list;

	if (!(list = (t_camera_list *)malloc(sizeof(t_camera_list))))
		error_exit(-19, "Can't create a t_camera_list array");
	// printf("malloc t_camera_list\n");

	*list = create_t_camera_list();

	return (list);
}

void			t_camera_list_push_back(t_camera_list *dest, t_camera to_add)
{
	t_camera *tmp;
	int i;

	if ((dest->size + 1) >= dest->max_size)
	{
		tmp = dest->camera;
		if (!(dest->camera = (t_camera *)malloc(sizeof(t_camera) * (dest->size + 1 + PUSH_SIZE))))
			error_exit(-20, "Can't realloc a t_camera array");
		// printf("malloc t_camera_list_push_back\n");
		i = 0;
		while (i < dest->size)
		{
			dest->camera[i] = tmp[i];
			i++;
		}
		free(tmp);
		dest->max_size += PUSH_SIZE;
	}
	dest->camera[dest->size] = to_add;
	(dest->size)++;
}

void			t_camera_list_add_back(t_camera_list *dest, t_camera *to_add)
{
	t_camera *tmp;
	int i;

	if ((dest->size + 1) >= dest->max_size)
	{
		tmp = dest->camera;
		if (!(dest->camera = (t_camera *)malloc(sizeof(t_camera) * (dest->size + 1 + PUSH_SIZE))))
			error_exit(-20, "Can't realloc a t_camera array");
		// printf("malloc t_camera_list_add_back\n");
		i = 0;
		while (i < dest->size)
		{
			dest->camera[i] = tmp[i];
			i++;
		}
		free(tmp);
		dest->max_size += PUSH_SIZE;
	}
	dest->camera[dest->size] = *to_add;
	(dest->size)++;
}

void			delete_t_camera_list(t_camera_list dest)
{
	free(dest.camera);
	// printf("delete t_camera_list\n");
}

void			free_t_camera_list(t_camera_list *dest)
{
	delete_t_camera_list(*dest);
	free(dest);
	// printf("free t_camera_list\n");
}

void			clean_t_camera_list(t_camera_list *dest)
{
	dest->size = 0;
}

t_camera			t_camera_list_at(t_camera_list *dest, int index)
{
	if (index < 0 || index >= dest->size)
		error_exit(-24, "Segfault : t_camera_list out of range");
	return (dest->camera[index]);
}

t_camera			*t_camera_list_get(t_camera_list *dest, int index)
{
	if (index < 0 || index >= dest->size)
		error_exit(-24, "Segfault : t_camera_list out of range");
	return (&(dest->camera[index]));
}
