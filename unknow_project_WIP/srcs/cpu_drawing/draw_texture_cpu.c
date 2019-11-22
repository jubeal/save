#include "unknow_project.h"

void	draw_triangle_texture_cpu(t_view_port *p_view_port, t_triangle *p_triangle, t_uv *p_uv)
{
	t_vector4		min;
	t_vector4		max;
	t_triangle		triangle;
	t_triangle		st;
	t_color			rgb;
	float			s;
	float			t;
	int				pixel_index;

	triangle.a = convert_opengl_to_vector4(p_view_port, p_triangle->a);
	triangle.b = convert_opengl_to_vector4(p_view_port, p_triangle->b);
	triangle.c = convert_opengl_to_vector4(p_view_port, p_triangle->c);

	st = create_t_triangle(create_t_vector4(p_uv->uv.a.x, p_uv->uv.a.y, p_uv->uv.a.z),
						create_t_vector4(p_uv->uv.b.x, p_uv->uv.b.y, p_uv->uv.b.z),
						create_t_vector4(p_uv->uv.c.x, p_uv->uv.c.y, p_uv->uv.c.z));

	// printf("z = %f --- w = %f\n", p_triangle->a.z, p_uv->uv.a.w);

	st.a.x /= p_triangle->a.w;
	st.a.y /= p_triangle->a.w;
	st.b.x /= p_triangle->b.w;
	st.b.y /= p_triangle->b.w;
	st.c.x /= p_triangle->c.w;
	st.c.y /= p_triangle->c.w;

	triangle.a.w = 1.0 / triangle.a.w;
	triangle.b.w = 1.0 / triangle.b.w;
	triangle.c.w = 1.0 / triangle.c.w;

	t_triangle_get_min_max_value(&triangle, &min, &max);

	if (min.x < 0)
		min.x = 0;
	if (min.y < 0)
		min.y = 0;
	if (max.x >= p_view_port->size.x)
		max.x = p_view_port->size.x - 1;
	if (max.y >= p_view_port->size.y)
		max.y = p_view_port->size.y - 1;
	t_vector4 w;
	t_vector4 pixelSample;
	float z;
	float area = edge_t_vector4(triangle.a, triangle.b, triangle.c);
	// printf("%f\n", area);
	for (int y = min.y; y <= max.y; y++)
	{
		pixel_index = (int)(min.x) + (y * p_view_port->size.x);
        for (int x = min.x; x <= max.x; x++)
		{
			pixelSample = create_t_vector4(x, y, 0);
			w = create_t_vector4(edge_t_vector4(triangle.b, triangle.c, pixelSample) / area,
											edge_t_vector4(triangle.c, triangle.a, pixelSample) / area,
											edge_t_vector4(triangle.a, triangle.b, pixelSample) / area);
			if (w.x >= 0 && w.y >= 0 && w.z >= 0)
			{
				z = 1 / ((triangle.a.w * w.x) + (triangle.b.w * w.y) + (triangle.c.w * w.z));
				if (z <= p_view_port->depth_buffer[pixel_index])
				{
					s = (w.x * st.a.x + w.y * st.b.x + w.z * st.c.x) * z * p_uv->texture->surface->w;
					t = (w.x * st.a.y + w.y * st.b.y + w.z * st.c.y) * z * p_uv->texture->surface->h;
					rgb = get_pixel_color(p_uv->texture, s, t);
					// printf("z = %f\n", z);
					p_view_port->depth_buffer[pixel_index] = z;
					draw_pixel(p_view_port->window, (int)(pixelSample.x + p_view_port->pos.x), (int)(pixelSample.y + p_view_port->pos.y), rgb);
				}
			}
			pixel_index++;
		}
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

void    draw_rectangle_texture_cpu(t_view_port *p_view_port, t_rectangle p_rec, t_texture *p_texture)
{
	static t_triangle_list	*tri_list = NULL;
	t_triangle				tri;
	static t_uv_list		*uv_list = NULL;
	t_uv					uv;

	if (tri_list == NULL && uv_list == NULL)
	{
		uv_list = initialize_t_uv_list();
		tri_list = initialize_t_triangle_list();
	}
	tri = create_t_triangle(create_t_vector4(p_rec.pos.x, p_rec.pos.y, 1.0),
							create_t_vector4(p_rec.pos.x + p_rec.size.x, p_rec.pos.y, 1.0),
							create_t_vector4(p_rec.pos.x, p_rec.pos.y + p_rec.size.y, 1.0));
	t_triangle_list_push_back(tri_list, tri);
	uv = create_t_uv(create_t_triangle(create_t_vector4(0, 1, 0), create_t_vector4(1, 1, 0), create_t_vector4(0, 0, 0)), p_texture);
	t_uv_list_push_back(uv_list, uv);

	tri = create_t_triangle(create_t_vector4(p_rec.pos.x + p_rec.size.x, p_rec.pos.y + p_rec.size.y, 1.0),
							create_t_vector4(p_rec.pos.x + p_rec.size.x, p_rec.pos.y, 1.0),
							create_t_vector4(p_rec.pos.x, p_rec.pos.y + p_rec.size.y, 1.0));
	t_triangle_list_push_back(tri_list, tri);
	uv = create_t_uv(create_t_triangle(create_t_vector4(1, 0, 0), create_t_vector4(1, 1, 0), create_t_vector4(0, 0, 0)), p_texture);
	t_uv_list_push_back(uv_list, uv);
	multithreading_draw_triangle_texture_cpu(p_view_port, tri_list, uv_list);
	clean_t_triangle_list(tri_list);
	clean_t_uv_list(uv_list);
}
