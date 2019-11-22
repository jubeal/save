#include "unknow_project.h"

t_vector4 create_t_vector4(float p_x, float p_y, float p_z)
{
	t_vector4 result;

	result.x = p_x;
	result.y = p_y;
	result.z = p_z;
	result.w = 1.0;

	return (result);
}

t_vector4	*initialize_t_vector4(float p_x, float p_y, float p_z)
{
	t_vector4 *result;

	if (!(result = (t_vector4 *)malloc(sizeof(t_vector4))))
		return (NULL);

	*result = create_t_vector4(p_x, p_y, p_z);

	return (result);
}

t_vector4	add_vector4_to_vector4(t_vector4 a, t_vector4 b)
{
	t_vector4	result;

	result = create_t_vector4(a.x + b.x, a.y + b.y, a.z + b.z);
	return (result);
}

t_vector4	substract_vector4_to_vector4(t_vector4 a, t_vector4 b)
{
	t_vector4	result;

	result = create_t_vector4(a.x - b.x, a.y - b.y, a.z - b.z);
	return (result);
}

t_vector4	substract_float_to_vector4(t_vector4 b, float a)
{
	t_vector4	result;

	result = create_t_vector4(b.x - a, b.y - a, b.z - a);
	return (result);
}

t_vector4	add_float_to_vector4(t_vector4 b, float a)
{
	t_vector4	result;

	result = create_t_vector4(b.x + a, b.y + a, b.z + a);
	return (result);
}

t_vector4	mult_vector4_by_vector4(t_vector4 a, t_vector4 b)
{
	t_vector4	result;

	result = create_t_vector4(a.x * b.x, a.y * b.y, a.z * b.z);
	return (result);
}

t_vector4	mult_vector4_by_float(t_vector4 a, float b)
{
	t_vector4	result;

	result = create_t_vector4(a.x * b, a.y * b, a.z * b);
	return (result);
}

t_vector4	divide_vector4_by_vector4(t_vector4 a, t_vector4 b)
{
	t_vector4	result;

	result = create_t_vector4(a.x / b.x, a.y / b.y, a.z / b.z);
	return (result);
}

t_vector4	divide_vector4_by_float(t_vector4 a, float b)
{
	t_vector4	result;

	result.x = a.x / b;
	result.y = a.y / b;
	result.z = a.z / b;
	result.w = a.w;
	return (result);
}

t_vector4	inv_t_vector4(t_vector4 src)
{
	t_vector4	result;

	result.x = -1 * src.x;
	result.y = -1 * src.y;
	result.z = -1 * src.z;
	result.w = -1 * src.w;
	return (result);
}

void		swap_t_vector4(t_vector4 *a, t_vector4 *b)
{
	t_vector4	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

int			t_vector4_equal(t_vector4 a, t_vector4 b)
{
	if (a.x != b.x || a.y != b.y || a.z != b.z)
		return (BOOL_FALSE);
	return (BOOL_TRUE);
}

float		t_vector4_length(t_vector4 a)
{
	return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}

void		print_t_vector4(t_vector4 vector, char *str) // A SUPPRIMER
{
	printf("%s : %0.4f / %0.4f / %0.4f / %0.4f\n", str, vector.x, vector.y, vector.z, vector.w);
}