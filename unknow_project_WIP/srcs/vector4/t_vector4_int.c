#include "unknow_project.h"

t_vector4_int create_t_vector4_int(int p_x, int p_y, int p_z)
{
	t_vector4_int result;

	result.x = p_x;
	result.y = p_y;
	result.z = p_z;
	result.w = 1.0;

	return (result);
}

t_vector4_int	*initialize_t_vector4_int(int p_x, int p_y, int p_z)
{
	t_vector4_int *result;

	if (!(result = (t_vector4_int *)malloc(sizeof(t_vector4_int))))
		return (NULL);

	*result = create_t_vector4_int(p_x, p_y, p_z);

	return (result);
}

void print_t_vector4_int(t_vector4_int vector, char *str)
{
	printf("%s%d / %d / %d / %d\n", str, vector.x, vector.y, vector.z, vector.w);
}
