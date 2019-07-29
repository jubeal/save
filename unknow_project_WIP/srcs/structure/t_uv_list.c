#include "unknow_project.h"


t_uv_list	create_t_uv_list()
{
	t_uv_list result;

	if (!(result.uvs = (t_uv *)malloc(sizeof(t_uv) * PUSH_SIZE)))
		error_exit(-55, "c pas bien");

	result.size = 0;
	result.max_size = PUSH_SIZE;

	return (result);
}

t_uv_list	*initialize_t_uv_list()
{
	t_uv_list *result;

	if (!(result = (t_uv_list *)malloc(sizeof(t_uv_list))))
		return (NULL);

	*result = create_t_uv_list();

	return (result);
}

void		t_uv_list_push_back(t_uv_list *dest, t_uv to_add)
{
	t_uv *tmp;
	int i;

	if ((dest->size + 1) >= dest->max_size)
	{
		tmp = dest->uvs;
		if (!(dest->uvs = (t_uv *)malloc(sizeof(t_uv) * (dest->size + 1 + PUSH_SIZE))))
			error_exit(-14, "Can't realloc a t_uv array");
		i = 0;
		while (i < dest->size)
		{
			dest->uvs[i] = tmp[i];
			i++;
		}
		free(tmp);
		dest->max_size += PUSH_SIZE;
	}
	dest->uvs[dest->size] = to_add;
	dest->size++;
}

void		t_uv_list_add_back(t_uv_list *dest, t_uv *to_add)
{
	t_uv *tmp;
	int i;

	if ((dest->size + 1) >= dest->max_size)
	{
		tmp = dest->uvs;
		if (!(dest->uvs = (t_uv *)malloc(sizeof(t_uv) * (dest->size + 1 + PUSH_SIZE))))
			error_exit(-14, "Can't realloc a t_uv array");
		i = 0;
		while (i < dest->size)
		{
			dest->uvs[i] = tmp[i];
			i++;
		}
		free(tmp);
		dest->max_size += PUSH_SIZE;
	}
	dest->uvs[dest->size].texture = to_add->texture;
	dest->uvs[dest->size].uv = to_add->uv;
	dest->size++;
}

t_uv	*t_uv_list_get(t_uv_list *dest, int index)
{
	if (index < 0 || index >= dest->size)
		error_exit(-28, "Segfault : t_color_list out of range");
	return (&dest->uvs[index]);
}

void	clean_t_uv_list(t_uv_list *dest)
{
	dest->size = 0;
}
