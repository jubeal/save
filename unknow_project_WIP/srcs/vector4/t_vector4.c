#include "unknow_project.h"

t_vector4 create_t_vector4(float p_x, float p_y, float p_z, float p_w)
{
	t_vector4 result;

	result.x = p_x;
	result.y = p_y;
	result.z = p_z;
	result.w = p_w;

	return (result);
}

t_vector4	*initialize_t_vector4(float p_x, float p_y, float p_z, float p_w)
{
	t_vector4 *result;

	if (!(result = (t_vector4 *)malloc(sizeof(t_vector4))))
		return (NULL);

	*result = create_t_vector4(p_x, p_y, p_z, p_w);

	return (result);
}

void print_t_vector4(t_vector4 vector, char *str)
{
	printf("%s%0.4f / %0.4f / %0.4f / %0.4f\n", str, vector.x, vector.y, vector.z, vector.w);
}
