#include "unknow_project.h"

t_vector2	create_t_vector2(float p_x, float p_y)
{
	t_vector2	result;

	result.x = p_x;
	result.y = p_y;
	return (result);
}

t_vector2	*initialize_t_vector2(float p_x, float p_y)
{
	t_vector2	*result;

	if (!(result = (t_vector2 *)malloc(sizeof(t_vector2))))
		return (NULL);
	*result = create_t_vector2(p_x, p_y);
	return (result);
}

void		t_vector2_swap(t_vector2 *a, t_vector2 *b)
{
	t_vector2 tmp;

	tmp.x = a->x;
	tmp.y = a->y;
	a->x = b->x;
	a->y = b->y;
	b->x = tmp.x;
	b->y = tmp.y;
}

void		t_vector2_add(t_vector2 *src, float delta_x, float delta_y)
{
	src->x += delta_x;
	src->y += delta_y;
}

void		set_t_vector2(t_vector2 *src, float p_x, float p_y)
{
	src->x = p_x;
	src->y = p_y;
}

t_vector2	add_vector2_to_vector2(t_vector2 v1, t_vector2 v2)
{
	t_vector2	result;

	result = create_t_vector2(v1.x + v2.x, v1.y + v2.y);
	return (result);
}

void		print_t_vector2(t_vector2 vector, char *str) // A SUPPRIMER
{
	printf("%s%0.20f / %0.20f\n", str, vector.x, vector.y);
}
