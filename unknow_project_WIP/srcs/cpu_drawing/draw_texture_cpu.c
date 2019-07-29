#include "unknow_project.h"

void	draw_triangle_texture_cpu(t_view_port *p_view_port, t_triangle *p_triangle, t_uv *p_uv)
{
	t_triangle	v;
	t_triangle	c;

	v = create_t_triangle(create_t_vector3(0.0, 0.0, 0.0), create_t_vector3(0.0, 0.0, 0.0), create_t_vector3(0.0, 0.0, 0.0));
	c = create_t_triangle(create_t_vector3(1.0, 0.0, 0.0), create_t_vector3(0.0, 1.0, 0.0), create_t_vector3(0.0, 0.0, 1.0));

	v.a.x = p_triangle->a.x / p_triangle->a.z;
	v.a.y = p_triangle->a.y / p_triangle->a.z;
	v.b.x = p_triangle->b.x / p_triangle->b.z;
	v.b.y = p_triangle->b.y / p_triangle->b.z;
	v.c.x = p_triangle->c.x / p_triangle->c.z;
	v.c.y = p_triangle->c.y / p_triangle->c.z;

	v.a.x = (1 + v.a.x) * 0.5 * p_view_port->window->size_x;
	v.a.y = (1 + v.a.y) * 0.5 * p_view_port->window->size_y;
	v.b.x = (1 + v.b.x) * 0.5 * p_view_port->window->size_x;
	v.b.y = (1 + v.b.y) * 0.5 * p_view_port->window->size_y;
	v.c.x = (1 + v.c.x) * 0.5 * p_view_port->window->size_x;
	v.c.y = (1 + v.c.y) * 0.5 * p_view_port->window->size_y;

	c.a.x /= p_triangle->a.z;
	c.a.y /= p_triangle->a.z;
	c.a.z /= p_triangle->a.z;
	c.b.x /= p_triangle->b.z;
	c.b.y /= p_triangle->b.z;
	c.b.z /= p_triangle->b.z;
	c.c.x /= p_triangle->c.z;
	c.c.y /= p_triangle->c.z;
	c.c.z /= p_triangle->c.z;

	v.a.z = 1 / v.a.z;
	v.b.z = 1 / v.b.z;
	v.c.z = 1 / v.c.z;

	t_color	color;
	color = create_t_color(1.0, 0.0, 0.0, 1.0);
	t_vector3	p;
	p = create_t_vector3(0.0, 0.0, 0.0);
	t_vector3	w;
	w = create_t_vector3(0.0, 0.0, 0.0);
	float		z;
	z = 0.0;

	float area = edge_t_vector3(v.a, v.b, v.c);
	int j = 0;
	while (j < p_view_port->window->size_y)
	{
		int i = 0;
		while (i < p_view_port->window->size_x)
		{
			p.x = (float)(i + 0.5);
			p.y = (float)(p_view_port->window->size_y - j + 0.5);
			p.z = 0.0;
			w.x = edge_t_vector3(v.b, v.c, p);
			w.y = edge_t_vector3(v.c, v.a, p);
			w.z = edge_t_vector3(v.a, v.b, p);
			if (w.x >= 0.0 && w.y >= 0.0 && w.z >= 0.0)
			{
				w.x /= area;
				w.y /= area;
				w.z /= area;
				color.r = w.x * c.a.x + w.y * c.b.x + w.z * c.c.x;
				color.g = w.x * c.a.y + w.y * c.b.y + w.z * c.c.y;
				color.b = w.x * c.a.z + w.y * c.b.z + w.z * c.c.z;
				// print_t_vector3(w, "vector w = ");
				// color = get_pixel_color(p_uv->texture, (int)w.x, (int)w.y);
				z = 1 / (w.x * v.a.z + w.y * v.b.z + w.z * v.c.z);
				printf("%f\n", 1 / (w.x * v.a.z + w.y * v.b.z + w.z * v.c.z));
				color.r *= z;
				color.g *= z;
				color.b *= z;
				draw_pixel(p_view_port->window, i, j, color);
			}
			i++;
		}
		j++;
	}

}

void	*thread_draw_texture_cpu(void *void_list)
{
	t_void_list 	*data;
	int				i;
	int				start;
	int				len;
	t_view_port 	*p_view_port;
	t_triangle_list	*triangle_list;
	t_uv_list	*uv_list;
	t_triangle		*triangle;
	t_uv		*uv;

	data = (t_void_list *)(void_list);
	start = (int)(t_void_list_at(data, 0));
	len = (int)(t_void_list_at(data, 1));
	p_view_port = (t_view_port *)(t_void_list_at(data, 2));
	triangle_list = (t_triangle_list *)(t_void_list_at(data, 3));
	uv_list = (t_uv_list *)(t_void_list_at(data, 4));
	i = 0;
	while (i < len && (start + i) < triangle_list->size)
	{
		triangle = t_triangle_list_get(triangle_list, start + i);
		uv = t_uv_list_get(uv_list, start + i);
		draw_triangle_texture_cpu(p_view_port, triangle, uv);
		i++;
	}
	pthread_exit(NULL);
}

void	multithreading_draw_triangle_texture_cpu(t_view_port *p_view_port, t_triangle_list *p_triangle_list, t_uv_list *p_uv_list)
{
	int start;
	int	modulo;
	int len;
	int i;
	int nb_thread;


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
		t_void_list_add_back(&p_view_port->window->data[i], 5, (long)start, (long)len, p_view_port, p_triangle_list, p_uv_list);
		pthread_create(&(p_view_port->window->threads[i]), NULL, thread_draw_texture_cpu, &(p_view_port->window->data[i]));
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

void    draw_rectangle_texture_cpu(t_view_port *p_view_port, t_vector2 p_pos, t_vector2 size, t_texture *p_texture)
{
	draw_triangle_texture_cpu(p_view_port, initialize_t_triangle(create_t_vector3(p_pos.x, p_pos.y, 0.0), create_t_vector3(p_pos.x + size.x, p_pos.y, 0.0), create_t_vector3(p_pos.x, p_pos.y + size.y, 0.0)),
													initialize_t_uv(create_t_triangle(create_t_vector3(0, 0, 0), create_t_vector3(1, 0, 0), create_t_vector3(0, 1, 0)), p_texture));
	draw_triangle_texture_cpu(p_view_port, initialize_t_triangle(create_t_vector3(p_pos.x + size.x, p_pos.y + size.y, 0.0), create_t_vector3(p_pos.x + size.x, p_pos.y, 0.0), create_t_vector3(p_pos.x, p_pos.y + size.y, 0.0)),
													initialize_t_uv(create_t_triangle(create_t_vector3(1, 1, 0), create_t_vector3(1, 0, 0), create_t_vector3(0, 1, 0)), p_texture));
}
