#include "unknow_project.h"

t_line		create_t_line(t_vector3 p_a, t_vector3 p_b)
{
	t_line result;

	result.a = p_a;
	result.b = p_b;

	return (result);
}

t_line		*initialize_t_line(t_vector3 p_a, t_vector3 p_b)
{
	t_line *result;

	if (!(result = (t_line *)malloc(sizeof(t_line))))
		error_exit(-31, "Can't malloc a t_line");

	*result = create_t_line(p_a, p_b);

	return (result);
}
