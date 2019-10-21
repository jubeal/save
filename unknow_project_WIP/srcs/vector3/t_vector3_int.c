#include "unknow_project.h"

t_vector3_int	create_t_vector3_int(int p_x, int p_y, int p_z)
{
	t_vector3_int	result;

	result.x = p_x;
	result.y = p_y;
	result.z = p_z;
	return (result);
}

t_vector3_int	*initialize_t_vector3_int(int p_x, int p_y, int p_z)
{
	t_vector3_int	*result;

	if (!(result = (t_vector3_int *)malloc(sizeof(t_vector3_int))))
		return (NULL);
	// printf("malloc t_vector3_int\n");
	*result = create_t_vector3_int(p_x, p_y, p_z);
	return (result);
}

void			t_vector3_int_swap(t_vector3_int *a, t_vector3_int *b)
{
	t_vector3_int tmp;

	tmp.x = a->x;
	tmp.y = a->y;
	tmp.z = a->z;
	a->x = b->x;
	a->y = b->y;
	a->z = b->z;
	b->x = tmp.x;
	b->y = tmp.y;
	b->z = tmp.z;
}

void			set_t_vector3_int(t_vector3_int *src, int p_x, int p_y, int p_z)
{
	src->x = p_x;
	src->y = p_y;
	src->z = p_z;
}

void			print_t_vector3_int(t_vector3_int vector, char *str) // A SUPPRIMER
{
	// printf("%s%d / %d / %d\n", str, vector.x, vector.y, vector.z);
}
