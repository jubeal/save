#include "unknow_project.h"

void	draw_triangle_texture_cpu(t_view_port *p_view_port, t_triangle *p_triangle, t_uv *p_uv)
{
	t_vector3		min;
	t_vector3		max;
	t_triangle		triangle;
	t_triangle		st;
	t_color			rgb;
	float			s;
	float			t;
	int				pixel_index;

	triangle.a = convert_opengl_to_vector3(p_view_port, p_triangle->a);
	triangle.b = convert_opengl_to_vector3(p_view_port, p_triangle->b);
	triangle.c = convert_opengl_to_vector3(p_view_port, p_triangle->c);

	st = create_t_triangle(create_t_vector3(p_uv->uv.a.x, p_uv->uv.a.y, p_uv->uv.a.z),
						create_t_vector3(p_uv->uv.b.x, p_uv->uv.b.y, p_uv->uv.b.z),
						create_t_vector3(p_uv->uv.c.x, p_uv->uv.c.y, p_uv->uv.c.z));

	st.a.x /= triangle.a.z;
	st.a.y /= triangle.a.z;
	st.b.x /= triangle.b.z;
	st.b.y /= triangle.b.z;
	st.c.x /= triangle.c.z;
	st.c.y /= triangle.c.z;

	triangle.a.z = 1.0 / triangle.a.z;
	triangle.b.z = 1.0 / triangle.b.z;
	triangle.c.z = 1.0 / triangle.c.z;

	t_triangle_get_min_max_value(&triangle, &min, &max);

	if (min.x < 0)
		min.x = 0;
	if (min.y < 0)
		min.y = 0;
	if (max.x >= p_view_port->size.x)
		max.x = p_view_port->size.x - 1;
	if (max.y >= p_view_port->size.y)
		max.y = p_view_port->size.y - 1;

	float area = edge_t_vector3(triangle.a, triangle.b, triangle.c);
	// printf("%f\n", area);
	for (int y = min.y; y <= max.y; y++)
	{
		pixel_index = (int)(min.x) + ((y) * p_view_port->size.x);
        for (int x = min.x; x <= max.x; x++)
		{
			t_vector3 pixelSample = create_t_vector3(x, y, 0);
			float w0 = edge_t_vector3(triangle.b, triangle.c, pixelSample) / area;
			float w1 = edge_t_vector3(triangle.c, triangle.a, pixelSample) / area;
			float w2 = edge_t_vector3(triangle.a, triangle.b, pixelSample) / area;
			if (w0 >= 0 && w1 >= 0 && w2 >= 0)
			{
				float z = 1 / ((triangle.a.z * w0) + (triangle.b.z * w1) + (triangle.c.z * w2));
				if (z <= p_view_port->depth_buffer[pixel_index])
				{
					s = (w0 * st.a.x + w1 * st.b.x + w2 * st.c.x) * z * p_uv->texture->surface->w;
					t = (w0 * st.a.y + w1 * st.b.y + w2 * st.c.y) * z * p_uv->texture->surface->h;
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

// {
// 	t_triangle tri;
// 	t_triangle c;
// 	t_triangle st;
// 	t_rasterizer	ab;
// 	t_rasterizer	ac;
// 	t_rasterizer	bc;

// 	// c = create_t_triangle(create_t_vector3(1, 0, 0),
// 	// 						create_t_vector3(0, 1, 0),
// 	// 						create_t_vector3(0, 0, 1));

// 	st = create_t_triangle(create_t_vector3(p_uv->uv.a.x, p_uv->uv.a.y, p_uv->uv.a.z),
// 							create_t_vector3(p_uv->uv.b.x, p_uv->uv.b.y, p_uv->uv.b.z),
// 							create_t_vector3(p_uv->uv.c.x, p_uv->uv.c.y, p_uv->uv.c.z));

// 	// tri.a.x /= tri.a.z;
// 	// tri.a.y /= tri.a.z;
// 	// tri.b.x /= tri.b.z;
// 	// tri.b.y /= tri.b.z;
// 	// tri.c.x /= tri.c.z;
// 	// tri.c.y /= tri.c.z;

// 	tri.a = convert_opengl_to_vector3(p_view_port, p_triangle->a);
// 	tri.b = convert_opengl_to_vector3(p_view_port, p_triangle->b);
// 	tri.c = convert_opengl_to_vector3(p_view_port, p_triangle->c);

// 	//perspective correcte
// 	// c.a.x /= tri.a.z;
// 	// c.a.y /= tri.a.z;
// 	// c.a.z /= tri.a.z;
// 	// c.b.x /= tri.b.z;
// 	// c.b.y /= tri.b.z;
// 	// c.b.z /= tri.b.z;
// 	// c.c.x /= tri.c.z;
// 	// c.c.y /= tri.c.z;
// 	// c.c.z /= tri.c.z;

// 	st.a.x /= tri.a.z;
// 	st.a.y /= tri.a.z;
// 	st.b.x /= tri.b.z;
// 	st.b.y /= tri.b.z;
// 	st.c.x /= tri.c.z;
// 	st.c.y /= tri.c.z;
// 	// print_t_triangle(tri, "tri = ");

// 	tri.a.z = 1.0 / p_triangle->a.z;
// 	tri.b.z = 1.0 / p_triangle->b.z;
// 	tri.c.z = 1.0 / p_triangle->c.z;

// 	ab = create_t_rasterizer(tri.a, tri.b, tri.c);
// 	ac = create_t_rasterizer(tri.a, tri.c, tri.b);
// 	bc = create_t_rasterizer(tri.b, tri.c, tri.a);

// 	t_vector3	min;
// 	t_vector3	max;

// 	int			i;
// 	int			j;

// 	t_triangle_get_min_max_value(&tri, &min, &max);

// 	if (min.x < 0)
// 		min.x = 0;
// 	if (min.y < 0)
// 		min.y = 0;
// 	if (max.x >= p_view_port->size.x)
// 		max.x = p_view_port->size.x - 1;
// 	if (max.y >= p_view_port->size.y)
// 		max.y = p_view_port->size.y - 1;
	
// 	i = min.x;
// 	j = min.y;

// 	t_vector3 p;
// 	t_vector3 w;
// 	t_color rgb;
// 	float z;
// 	float s;
// 	float t;
// 	float area = edge_t_vector3(tri.a, tri.b, tri.c);
// 	int pixel_index;
// 	// printf("%f\n", area);
// 	while (j < max.y)
// 	{
// 		i = min.x;
// 		while (i < max.x)
// 		{
// 			p = create_t_vector3(i + EPSILON, j + EPSILON, 0);
// 			w = create_t_vector3(calc_rasterizer(&bc, i, j) / area,
// 								calc_rasterizer(&ac, i, j) / area,
// 								calc_rasterizer(&ab, i, j) / area);
// 			if (w.x >= 0.0 && w.y >= 0.0 && w.z >= 0.0)
// 			{
// 				z = 1 / (w.x * tri.a.z + w.y * tri.b.z + w.z * tri.c.z);
// 				if (z <= p_view_port->depth_buffer[pixel_index])
// 				{
// 					s = (w.x * st.a.x + w.y * st.b.x + w.z * st.c.x) * z * p_uv->texture->surface->w;
// 					t = (w.x * st.a.y + w.y * st.b.y + w.z * st.c.y) * z * p_uv->texture->surface->h;
// 					rgb = get_pixel_color(p_uv->texture, s, t);
// 					// printf("z = %f\n", z);
// 					p_view_port->depth_buffer[i + (j * p_view_port->window->size_x)] = z;
// 					draw_pixel(p_view_port->window, (int)(p.x + p_view_port->pos.x), (int)(p.y + p_view_port->pos.y), rgb);
// 				}
// 			}
// 			i++;
// 		}
// 		j++;
// 	}
// }

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
	t_triangle_list	*tri_list;
	t_triangle		*tri;
	t_uv_list		*uv_list;
	t_uv			*uv;

	uv_list = initialize_t_uv_list();
	tri_list = initialize_t_triangle_list();
	tri = initialize_t_triangle(create_t_vector3(p_rec.pos.x, p_rec.pos.y, 1.0),
							create_t_vector3(p_rec.pos.x + p_rec.size.x, p_rec.pos.y, 1.0),
							create_t_vector3(p_rec.pos.x, p_rec.pos.y + p_rec.size.y, 1.0));
	t_triangle_list_push_back(tri_list, *tri);
	uv = initialize_t_uv(create_t_triangle(create_t_vector3(0, 1, 0), create_t_vector3(1, 1, 0), create_t_vector3(0, 0, 0)), p_texture);
	t_uv_list_push_back(uv_list, *uv);

	tri = initialize_t_triangle(create_t_vector3(p_rec.pos.x + p_rec.size.x, p_rec.pos.y + p_rec.size.y, 1.0),
							create_t_vector3(p_rec.pos.x + p_rec.size.x, p_rec.pos.y, 1.0),
							create_t_vector3(p_rec.pos.x, p_rec.pos.y + p_rec.size.y, 1.0));
	t_triangle_list_push_back(tri_list, *tri);
	uv = initialize_t_uv(create_t_triangle(create_t_vector3(1, 0, 0), create_t_vector3(1, 1, 0), create_t_vector3(0, 0, 0)), p_texture);
	t_uv_list_push_back(uv_list, *uv);
	multithreading_draw_triangle_texture_cpu(p_view_port, tri_list,	uv_list);
}
