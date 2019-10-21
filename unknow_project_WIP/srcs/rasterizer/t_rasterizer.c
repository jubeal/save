#include "unknow_project.h"

t_rasterizer	create_t_rasterizer(t_vector3 a, t_vector3 b, t_vector3 c)
{
	t_rasterizer	result;

	result.a = (a.y - b.y);
	result.b = (b.x - a.x);
	result.c = (a.x * b.y) - (a.y * b.x);
	result.max = apply_formula(&result, c.x, c.y);
	return (result);
}

t_rasterizer	*initialize_t_rasterizer(t_vector3 a, t_vector3 b, t_vector3 c)
{
	t_rasterizer	*result;

	if (!(result = (t_rasterizer *)malloc(sizeof(t_rasterizer))))
		error_exit(-13, "Can't create a t_rasterizer");
	// printf("malloc t_rasterizer\n");
	*result = create_t_rasterizer(a, b, c);
	return (result);
}

float			apply_formula(t_rasterizer *rast, float x, float y)
{
	return (rast->a * x + rast->b * y + rast->c);
}

float			calc_rasterizer(t_rasterizer *rast, float x, float y)
{
	return (apply_formula(rast, x, y) / rast->max);
}
