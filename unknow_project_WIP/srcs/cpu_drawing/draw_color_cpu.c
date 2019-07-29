#include "unknow_project.h"

int find;

void	draw_triangle_color_cpu(t_view_port *view_port, t_triangle *p_triangle, t_color *p_color)
{
	t_vector3		min;
	t_vector3		max;
	t_triangle		triangle;
	int				pixel_index;

	triangle.a = convert_opengl_to_vector3(view_port, p_triangle->a);
	triangle.b = convert_opengl_to_vector3(view_port, p_triangle->b);
	triangle.c = convert_opengl_to_vector3(view_port, p_triangle->c);

	triangle.a.z = 1.0 / triangle.a.z;
	triangle.b.z = 1.0 / triangle.b.z;
	triangle.c.z = 1.0 / triangle.c.z;

	t_triangle_get_min_max_value(&triangle, &min, &max);

	if (min.x < 0)
		min.x = 0;
	if (min.y < 0)
		min.y = 0;
	if (max.x >= view_port->size.x)
		max.x = view_port->size.x - 1;
	if (max.y >= view_port->size.y)
		max.y = view_port->size.y - 1;

	float area = edge_t_vector3(triangle.a, triangle.b, triangle.c);

	for (int y = min.y; y <= max.y; y++)
	{
		pixel_index = (int)(min.x) + ((y) * view_port->size.x);
        for (int x = min.x; x <= max.x; x++)
		{
			t_vector3 pixelSample = create_t_vector3(x, y, 0);
			float w0 = edge_t_vector3(triangle.b, triangle.c, pixelSample) / area;
			float w1 = edge_t_vector3(triangle.c, triangle.a, pixelSample) / area;
			float w2 = edge_t_vector3(triangle.a, triangle.b, pixelSample) / area;
			if (w0 >= 0 && w1 >= 0 && w2 >= 0)
			{
				float oneOverZ = (triangle.a.z * w0) + (triangle.b.z * w1) + (triangle.c.z * w2);
				float z = 1 / oneOverZ;
				if (z <= view_port->depth_buffer[pixel_index])
				{
					view_port->depth_buffer[pixel_index] = z;
					draw_pixel(view_port->window, (int)(pixelSample.x + view_port->pos.x), (int)(pixelSample.y + view_port->pos.y), *p_color);
				}
			}
			pixel_index++;
		}
	}
}

void	*thread_draw_color_cpu(void *void_list)
{
	t_void_list 	*data;
	int				i;
	int				start;
	int				len;
	t_view_port 	*view_port;
	t_triangle_list	*triangle_list;
	t_color_list	*color_list;
	t_triangle		*triangle;
	t_color			*color;

	data = (t_void_list *)(void_list);
	start = (int)(t_void_list_at(data, 0));
	len = (int)(t_void_list_at(data, 1));
	view_port = (t_view_port *)(t_void_list_at(data, 2));
	triangle_list = (t_triangle_list *)(t_void_list_at(data, 3));
	color_list = (t_color_list *)(t_void_list_at(data, 4));
	i = 0;
	while (i < len && (start + i) < triangle_list->size)
	{
		triangle = t_triangle_list_get(triangle_list, start + i);
		color = t_color_list_get(color_list, start + i);
		draw_triangle_color_cpu(view_port, triangle, color);
		i++;
	}
	pthread_exit(NULL);
}

void	multithreading_draw_triangle_color_cpu(t_view_port *p_view_port, t_triangle_list *p_triangle_list, t_color_list *p_color_list)
{
	int start;
	int	modulo;
	int len;
	int i;
	int nb_thread;

	find = 0;
	start = 0;
	modulo = p_triangle_list->size % NB_THREAD_MAX;
	i = 0;
	nb_thread = p_triangle_list->size / (NB_TRIANGLE_MAX);
	if (nb_thread == 0)
		nb_thread++;
	if (nb_thread >= NB_THREAD_MAX)
		nb_thread = NB_THREAD_MAX;
	while (i < nb_thread)
	{
		len = p_triangle_list->size / nb_thread;
		if (i < modulo)
			len++;
		clean_t_void_list(&(p_view_port->window->data[i]));
		t_void_list_add_back(&p_view_port->window->data[i], 5, (long)start, (long)len, p_view_port, p_triangle_list, p_color_list);
		pthread_create(&(p_view_port->window->threads[i]), NULL, thread_draw_color_cpu, &(p_view_port->window->data[i]));
		i++;
		start += len;
	}
	i = 0;
	while (i < nb_thread)
	{
		pthread_join(p_view_port->window->threads[i], NULL); // join et free des threads
		i++;
	}
}

void    draw_rectangle_color_cpu(t_view_port *p_view_port, t_vector2 p_pos, t_vector2 size, t_color *p_color)
{
	draw_triangle_color_cpu(p_view_port, initialize_t_triangle(create_t_vector3(p_pos.x, p_pos.y, 0.0), create_t_vector3(p_pos.x + size.x, p_pos.y, 0.0), create_t_vector3(p_pos.x, p_pos.y + size.y, 0.0)), p_color);
	draw_triangle_color_cpu(p_view_port, initialize_t_triangle(create_t_vector3(p_pos.x + size.x, p_pos.y + size.y, 0.0), create_t_vector3(p_pos.x + size.x, p_pos.y, 0.0), create_t_vector3(p_pos.x, p_pos.y + size.y, 0.0)), p_color);
}
