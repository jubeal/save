#include "unknow_project.h"

t_vector2_int	create_t_vector2_int(int p_x, int p_y)
{
	t_vector2_int	result;

	result.x = p_x;
	result.y = p_y;
	return (result);
}

t_vector2_int	*initialize_t_vector2_int(int p_x, int p_y)
{
	t_vector2_int	*result;

	if (!(result = (t_vector2_int *)malloc(sizeof(t_vector2_int))))
		return (NULL);
	// printf("malloc t_vector2_int\n");
	*result = create_t_vector2_int(p_x, p_y);
	return (result);
}

void			t_vector2_int_swap(t_vector2_int *a, t_vector2_int *b)
{
	t_vector2_int	tmp;

	tmp.x = a->x;
	tmp.y = a->y;
	a->x = b->x;
	a->y = b->y;
	b->x = tmp.x;
	b->y = tmp.y;
}

void			t_vector2_int_add(t_vector2_int *src, int delta_x, int delta_y)
{
	src->x += delta_x;
	src->y += delta_y;
}

void			set_t_vector2_int(t_vector2_int *src, int p_x, int p_y)
{
	src->x = p_x;
	src->y = p_y;
}

void			print_t_vector2_int(t_vector2_int vector, char *str) //A SUPPRIMER
{
	// printf("%s%d / %d\n", str, vector.x, vector.y);
}
