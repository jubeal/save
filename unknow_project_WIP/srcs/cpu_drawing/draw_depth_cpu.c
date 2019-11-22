#include "unknow_project.h"

void	draw_triangle_depth_cpu(t_view_port *view_port, t_triangle *p_triangle, float dist_max)
{
	t_color			color;
	t_triangle		triangle;
	t_vector4		min;
	t_vector4		max;
	t_vector4		current;
	t_rasterizer	ab;
	t_rasterizer	ac;
	t_rasterizer	bc;
	float			alpha;
	float			beta;
	float			gamma;
	int				pixel_index;
	float			z;

	color.a = 1.0f;

	triangle.a = convert_opengl_to_vector4(view_port, p_triangle->a);
	triangle.b = convert_opengl_to_vector4(view_port, p_triangle->b);
	triangle.c = convert_opengl_to_vector4(view_port, p_triangle->c);

	triangle.a.z = 1.0 / triangle.a.z;
	triangle.b.z = 1.0 / triangle.b.z;
	triangle.c.z = 1.0 / triangle.c.z;

	ab = create_t_rasterizer(triangle.a, triangle.b, triangle.c);
	ac = create_t_rasterizer(triangle.a, triangle.c, triangle.b);
	bc = create_t_rasterizer(triangle.b, triangle.c, triangle.a);

	t_triangle_get_min_max_value(&triangle, &min, &max);

	float area = edge_t_vector4(triangle.a, triangle.b, triangle.c);

	if (min.x < 0)
		min.x = 0;
	if (min.y < 0)
		min.y = 0;
	if (max.x >= view_port->size.x)
		max.x = view_port->size.x - 1;
	if (max.y >= view_port->size.y)
		max.y = view_port->size.y - 1;

	current = min;
	while (current.y <= max.y)
	{
		pixel_index = (int)(current.x) + ((int)(current.y) * view_port->size.x);

		while (current.x <= max.x)
		{
			alpha = calc_rasterizer(&ab, current.x, current.y);
			beta = calc_rasterizer(&ac, current.x, current.y);
			gamma = (1.0 - alpha - beta);
			if (alpha >= 0 && beta >= 0 && gamma >= 0)
			{
				z = 1 / ((triangle.a.z * gamma) + (triangle.b.z * beta) + (triangle.c.z * alpha));

				color.r = 1.0 - (z / dist_max);
				color.g = 1.0 - (z / dist_max);
				color.b = 1.0 - (z / dist_max);

				if (z <= view_port->depth_buffer[pixel_index] || view_port->depth_buffer[pixel_index] == -1)
				{
					draw_pixel(view_port->window, (int)(current.x), (int)(current.y), color);
					view_port->depth_buffer[pixel_index] = z;
				}
			}
			current.x++;
			pixel_index++;
		}
		current.x = min.x;
		current.y++;
	}
}
