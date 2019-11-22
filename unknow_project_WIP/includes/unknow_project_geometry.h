#ifndef UNKNOW_PROJECT_GEOMETRY_H
# define UNKNOW_PROJECT_GEOMETRY_H

# include "unknow_project_vector.h"

typedef struct	s_triangle
{
	t_vector4	a;
	t_vector4	b;
	t_vector4	c;
}				t_triangle;

t_triangle		create_t_triangle(t_vector4 p_a, t_vector4 p_b, t_vector4 p_c);
t_triangle		*initialize_t_triangle(t_vector4 p_a, t_vector4 p_b, t_vector4 p_c);
void			sort_t_triangles(t_triangle *a, t_triangle *b);
void 			sort_t_triangle_points(t_triangle *p_triangle);
void			print_t_triangle(t_triangle p_triangle, char *triangle_name);
t_triangle		t_triangle_add_vector4(t_triangle triangle, t_vector4 to_add);
t_triangle		mult_triangle_by_vector4(t_triangle triangle, t_vector4 to_add);
void			t_triangle_get_min_max_value(t_triangle *triangle, t_vector4 *min, t_vector4 *max);
int				t_triangle_equal(t_triangle a, t_triangle b);
int				t_triangle_is_bigger(t_triangle a, t_triangle b);
int				t_triangle_similarity(t_triangle a, t_triangle b);
int				t_triangle_similarity_segment(t_triangle p_a, t_vector4 p_b, t_vector4 p_c);
int 			is_triangle_contact(t_triangle a, t_triangle b);

typedef struct	s_line
{
	t_vector4	a;
	t_vector4	b;
}				t_line;

t_line			create_t_line(t_vector4 p_a, t_vector4 p_b);
t_line			*initialize_t_line(t_vector4 p_a, t_vector4 p_b);
void			print_t_line(t_line line, char *str);

typedef struct	s_rectangle
{
	t_vector2	pos;
	t_vector2	size;
}				t_rectangle;

t_rectangle		create_t_rectangle(t_vector2 p_pos, t_vector2 p_size);
t_rectangle		*initialize_t_rectangle(t_vector2 p_pos, t_vector2 p_size);

#endif
