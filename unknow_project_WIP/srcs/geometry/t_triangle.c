#include "unknow_project.h"

t_triangle create_t_triangle(t_vector3 p_a, t_vector3 p_b, t_vector3 p_c)
{
	t_triangle result;

	result.a = p_a;
	result.b = p_b;
	result.c = p_c;

	return (result);
}

t_triangle	*initialize_t_triangle(t_vector3 p_a, t_vector3 p_b, t_vector3 p_c)
{
	t_triangle *result;

	if (!(result = (t_triangle *)malloc(sizeof(t_triangle))))
		error_exit(-31, "Can't malloc a t_triangle");

	*result = create_t_triangle(p_a, p_b, p_c);

	return (result);
}

void		sort_t_triangles(t_triangle *a, t_triangle *b)
{
	t_triangle tmp;

	sort_t_triangle_points(a);
	sort_t_triangle_points(b);

	if (t_triangle_is_bigger(*a, *b) == BOOL_FALSE)
	{
		tmp = *a;
		*a = *b;
		*b = tmp;
	}
}

void 		sort_t_triangle_points(t_triangle *p_triangle)
{
	if (p_triangle->a.y > p_triangle->b.y || (p_triangle->a.y == p_triangle->b.y && p_triangle->a.x > p_triangle->b.x))
	{
		swap_t_vector3(&(p_triangle->a), &(p_triangle->b));
	}
	if (p_triangle->b.y > p_triangle->c.y || (p_triangle->b.y == p_triangle->c.y && p_triangle->b.x > p_triangle->c.x))
	{
		swap_t_vector3(&(p_triangle->b), &(p_triangle->c));
	}
	if (p_triangle->a.y > p_triangle->b.y || (p_triangle->a.y == p_triangle->b.y && p_triangle->a.x > p_triangle->b.x))
	{
		swap_t_vector3(&(p_triangle->a), &(p_triangle->b));
	}
}

t_triangle		t_triangle_add_vector3(t_triangle triangle, t_vector3 to_add)
{
	t_triangle result;

	result.a = add_vector3_to_vector3(triangle.a, to_add);
	result.b = add_vector3_to_vector3(triangle.b, to_add);
	result.c = add_vector3_to_vector3(triangle.c, to_add);

	return (result);
}

void		print_t_triangle(t_triangle p_triangle, char *triangle_name)
{
	printf("Triangle Name : %s\n", triangle_name);
	print_t_vector3(p_triangle.a, "A : ");
	print_t_vector3(p_triangle.b, "B : ");
	print_t_vector3(p_triangle.c, "C : ");
}

t_triangle	mult_triangle_by_vector3(t_triangle triangle, t_vector3 to_add)
{
	t_triangle result;

	result.a = mult_vector3_by_vector3(triangle.a, to_add);
	result.b = mult_vector3_by_vector3(triangle.b, to_add);
	result.c = mult_vector3_by_vector3(triangle.c, to_add);

	return (result);
}

t_triangle		compose_t_triangle_from_t_mesh(t_mesh *src, int *index)
{
	t_triangle result;
	int i;

	i = 0;
	while (i < 3)
	{
		if (src->vertices->size <= index[i])
			error_exit(-14, "can't compose a triangle");
		i++;
	}

	result.a = add_vector3_to_vector3(t_vector3_list_at(src->vertices, index[0]), src->pos);
	result.b = add_vector3_to_vector3(t_vector3_list_at(src->vertices, index[1]), src->pos);
	result.c = add_vector3_to_vector3(t_vector3_list_at(src->vertices, index[2]), src->pos);

	return (result);
}

t_triangle		compose_t_triangle_from_t_vertices(t_vector3_list *src, int *index)
{
	t_triangle result;
	int i;

	i = 0;
	while (i < 3)
	{
		if (src->size <= index[i])
			error_exit(-14, "can't compose a triangle");
		i++;
	}

	result.a = t_vector3_list_at(src, index[0]);
	result.b = t_vector3_list_at(src, index[1]);
	result.c = t_vector3_list_at(src, index[2]);

	return (result);
}

void			t_triangle_get_min_max_value(t_triangle *triangle, t_vector3 *min, t_vector3 *max)
{
	max->x = get_big_float(triangle->a.x, triangle->b.x, triangle->c.x);
	max->y = get_big_float(triangle->a.y, triangle->b.y, triangle->c.y);
	max->z = get_big_float(triangle->a.z, triangle->b.z, triangle->c.z);
	min->x = get_short_float(triangle->a.x, triangle->b.x, triangle->c.x);
	min->y = get_short_float(triangle->a.y, triangle->b.y, triangle->c.y);
	min->z = get_short_float(triangle->a.z, triangle->b.z, triangle->c.z);
}

int				t_triangle_is_bigger(t_triangle a, t_triangle b)
{
	float p1a;
	float p1b;
	float p1c;
	float p2a;
	float p2b;
	float p2c;

	float p1;
	float p2;

	float s1;
	float s2;

	p1a = calc_dist_vector3_to_vector3(a.a, a.b);
	p1b = calc_dist_vector3_to_vector3(a.a, a.c);
	p1c = calc_dist_vector3_to_vector3(a.b, a.c);
	p2a = calc_dist_vector3_to_vector3(b.a, b.b);
	p2b = calc_dist_vector3_to_vector3(b.a, b.c);
	p2c = calc_dist_vector3_to_vector3(b.b, b.c);

	p1 = p1a + p1b + p1c;
	p2 = p2a + p2b + p2c;

	s1 = sqrt(p1 * (p1 - p1a) * (p1 - p1b) * (p1 * p1c));
	s2 = sqrt(p2 * (p2 - p2a) * (p2 - p2b) * (p2 * p2c));

	if (s1 >= s2)
		return (BOOL_TRUE);
	return (BOOL_FALSE);
}

int				t_triangle_equal(t_triangle a, t_triangle b)
{
	sort_t_triangle_points(&a);
	sort_t_triangle_points(&b);

	if (t_vector3_equal(a.a, b.a) == BOOL_FALSE ||
		t_vector3_equal(a.b, b.b) == BOOL_FALSE ||
		t_vector3_equal(a.c, b.c) == BOOL_FALSE)
		return (BOOL_FALSE);
	return (BOOL_TRUE);
}

int				t_triangle_similarity(t_triangle p_a, t_triangle p_b)
{
	t_vector3	a[3];
	t_vector3	b[3];
	int			result;
	int			i;
	int			j;

	a[0] = p_a.a;
	a[1] = p_a.b;
	a[2] = p_a.c;
	b[0] = p_b.a;
	b[1] = p_b.b;
	b[2] = p_b.c;
	result = 0;
	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			if (t_vector3_equal(a[i], b[j]) == BOOL_TRUE)
				result++;
			j++;
		}
		i++;
	}
	return (result);
}

int				t_triangle_similarity_segment(t_triangle p_a, t_vector3 p_b, t_vector3 p_c)
{
	t_vector3	a[3];
	t_vector3	b[2];
	int			result;
	int			i;
	int			j;

	a[0] = p_a.a;
	a[1] = p_a.b;
	a[2] = p_a.c;
	b[0] = p_b;
	b[1] = p_c;
	result = 0;
	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 2)
		{
			if (t_vector3_equal(a[i], b[j]) == BOOL_TRUE)
				result++;
			j++;
		}
		i++;
	}
	return (result);
}