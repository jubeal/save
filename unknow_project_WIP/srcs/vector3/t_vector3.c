#include "unknow_project.h"

t_vector3	create_t_vector3(float p_x, float p_y, float p_z)
{
	t_vector3	result;

	result.x = p_x;
	result.y = p_y;
	result.z = p_z;
	return (result);
}

t_vector3	*initialize_t_vector3(float p_x, float p_y, float p_z)
{
	t_vector3	*result;

	if (!(result = (t_vector3 *)malloc(sizeof(t_vector3))))
		return (NULL);
	// printf("malloc t_vector3\n");
	*result = create_t_vector3(p_x, p_y, p_z);
	return (result);
}

t_vector3	add_vector3_to_vector3(t_vector3 a, t_vector3 b)
{
	t_vector3	result;

	result = create_t_vector3(a.x + b.x, a.y + b.y, a.z + b.z);
	return (result);
}

t_vector3	substract_vector3_to_vector3(t_vector3 a, t_vector3 b)
{
	t_vector3	result;

	result = create_t_vector3(a.x - b.x, a.y - b.y, a.z - b.z);
	return (result);
}

t_vector3	substract_float_to_vector3(t_vector3 b, float a)
{
	t_vector3	result;

	result = create_t_vector3(b.x - a, b.y - a, b.z - a);
	return (result);
}

t_vector3	add_float_to_vector3(t_vector3 b, float a)
{
	t_vector3	result;

	result = create_t_vector3(b.x + a, b.y + a, b.z + a);
	return (result);
}

t_vector3	mult_vector3_by_vector3(t_vector3 a, t_vector3 b)
{
	t_vector3	result;

	result = create_t_vector3(a.x * b.x, a.y * b.y, a.z * b.z);
	return (result);
}

t_vector3	mult_vector3_by_float(t_vector3 a, float b)
{
	t_vector3	result;

	result = create_t_vector3(a.x * b, a.y * b, a.z * b);
	return (result);
}

t_vector3	divide_vector3_by_vector3(t_vector3 a, t_vector3 b)
{
	t_vector3	result;

	result = create_t_vector3(a.x / b.x, a.y / b.y, a.z / b.z);
	return (result);
}

t_vector3	divide_vector3_by_float(t_vector3 a, float b)
{
	t_vector3	result;

	result = create_t_vector3(a.x / b, a.y / b, a.z / b);
	return (result);
}

t_vector3	inv_t_vector3(t_vector3 src)
{
	t_vector3	result;

	result.x = -1 * src.x;
	result.y = -1 * src.y;
	result.z = -1 * src.z;
	return (result);
}

void		swap_t_vector3(t_vector3 *a, t_vector3 *b)
{
	t_vector3	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

int			t_vector3_equal(t_vector3 a, t_vector3 b)
{
	if (a.x != b.x || a.y != b.y || a.z != b.z)
		return (BOOL_FALSE);
	return (BOOL_TRUE);
}

float		t_vector3_length(t_vector3 a)
{
	return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}

void		print_t_vector3(t_vector3 vector, char *str) // A SUPPRIMER
{
	printf("%s : %0.4f / %0.4f / %0.4f\n", str, vector.x, vector.y, vector.z);
}
