#include "unknow_project.h"

t_item_list 	create_t_item_list()
{
	t_item_list	list;

	if (!(list.item = (t_item *)malloc(sizeof(t_item) * PUSH_SIZE)))
		error_exit(-18, "Can't malloc a t_item array");
	// printf("malloc t_item_list.item\n");
	list.size = 0;
	list.max_size = PUSH_SIZE;
	return (list);
}

t_item_list 	*initialize_t_item_list()
{
	t_item_list *list;

	if (!(list = (t_item_list *)malloc(sizeof(t_item_list))))
		error_exit(-19, "Can't create a t_item_list array");
	// printf("malloc t_item_list\n");
	*list = create_t_item_list();

	return (list);
}

void			t_item_list_push_back(t_item_list *dest, t_item to_add)
{
	t_item *tmp;
	int i;

	if ((dest->size + 1) >= dest->max_size)
	{
		tmp = dest->item;
		if (!(dest->item = (t_item *)malloc(sizeof(t_item) * (dest->size + 1 + PUSH_SIZE))))
			error_exit(-20, "Can't realloc a t_item array");
		// printf("malloc t_item_list_push_back\n");
		i = 0;
		while (i < dest->size)
		{
			dest->item[i] = tmp[i];
			i++;
		}
		free(tmp);
		dest->max_size += PUSH_SIZE;
	}
	dest->item[dest->size] = to_add;
	(dest->size)++;
}

void			t_item_list_erase(t_item_list *dest, int index)
{
	free_t_item(t_item_list_get(dest, index));
	while (index < dest->size)
	{
		dest[index + 1] = dest[index];
		index++;
	}
}

void			delete_t_item_list(t_item_list dest)
{
	free(dest.item);
	// printf("delete t_item_list\n");
}

void			free_t_item_list(t_item_list *dest)
{
	delete_t_item_list(*dest);
	free(dest);
	// printf("free t_item_list\n");
}

void			clean_t_item_list(t_item_list *dest)
{
	dest->size = 0;
}

t_item			t_item_list_at(t_item_list *dest, int index)
{
	if (index < 0 || index >= dest->size)
		error_exit(-24, "Segfault : t_item_list out of range");
	return (dest->item[index]);
}

t_item			*t_item_list_get(t_item_list *dest, int index)
{
	if (index < 0 || index >= dest->size)
		error_exit(-24, "Segfault : t_item_list out of range");
	return (&(dest->item[index]));
}

int			t_item_list_get_index(t_item_list *dest, t_item *item)
{
	int i;

	i = 0;
	while (i < dest->size)
	{
		if (dest[i].item == item)
			return (i);
		i++;
	}
	return (-1);
}
