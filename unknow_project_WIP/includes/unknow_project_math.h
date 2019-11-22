#ifndef UNKNOW_PROJECT_MATH_H
# define UNKNOW_PROJECT_MATH_H

# include "unknow_project_vector.h"
# include "unknow_project_basic_list.h"

typedef struct	s_matrix
{
	float		value[4][4];
}				t_matrix;

t_matrix 		create_t_matrix();
t_matrix 		*initialize_t_matrix();
t_matrix 		create_t_matrix_empty();
t_matrix 		create_translation_matrix(t_vector4 translation);
t_matrix 		create_scaling_matrix(t_vector4 scaling);
t_matrix 		create_rotation_x_matrix(float angle);
t_matrix 		create_rotation_y_matrix(float angle);
t_matrix 		create_rotation_z_matrix(float angle);
t_matrix 		create_rotation_matrix(float x, float y, float z);
t_matrix 		mult_matrix_by_matrix(t_matrix m1, t_matrix m2);
t_vector4 		mult_vector4_by_matrix(t_vector4 vertex, t_matrix m);
void			print_t_matrix(t_matrix *m);

typedef struct	s_rasterizer
{
	float 		a;
	float 		b;
	float 		c;
	float		max;
} 				t_rasterizer;

t_rasterizer 	create_t_rasterizer(t_vector4 s, t_vector4 e, t_vector4 ext);
t_rasterizer	*initialize_t_rasterizer(t_vector4 s, t_vector4 e, t_vector4 ext);
float 			apply_formula(t_rasterizer *rast, float x, float y);
float			calc_rasterizer(t_rasterizer *rast, float x, float y);


char			*ft_itoa(int n);
int				generate_nbr(int min, int max);
t_vector2_int_list
				calc_line(t_vector2_int start, t_vector2_int end);
t_vector4		cross_t_vector4(t_vector4 a, t_vector4 b);
t_vector4 		normalize_t_vector4(t_vector4 v);
float			dot_t_vector4(t_vector4 a, t_vector4 b);
float			edge_t_vector4(t_vector4 a, t_vector4 b, t_vector4 c);
int				intersect_segment_by_segment(t_vector4 a, t_vector4 b, t_vector4 c, t_vector4 d);
t_vector4		intersect_plane_by_line(t_vector4 p_normal, t_vector4 p_center, t_vector4 start, t_vector4 end);
int				intersect_triangle_by_segment(t_triangle p_triangle, t_vector4 p_normal, t_line line, t_vector4 *intersection);
int				is_point_on_line(t_vector4 a, t_vector4 b, t_vector4 c);
float			calc_distance_to_triangle(t_triangle p_triangle, t_vector4 point);
float			calc_distance_to_plane(t_vector4 p_normal, t_vector4 p_center, t_vector4 p_point);
float			clamp_float_value(float min, float value, float max);
float			calc_dist_vector4_to_vector4(t_vector4 a, t_vector4 b);
int				clamp_int_value(int min, int value, int max);
t_vector4		interpolate_vector4_over_line(float ratio_x, float ratio_y, t_vector4 ua, t_vector4 ub);
float			interpolate_ratio(float a, float b, float c);
int				get_short(int a, int b, int c);
int				get_big(int a, int b, int c);
float			get_short_float(float a, float b, float c);
float			get_big_float(float a, float b, float c);

int				is_point_on_triangle(t_triangle a, t_vector4 point);
int				is_triangle_parallele(t_triangle p_a, t_triangle p_b);
int 			is_triangle_cut_triangle(t_triangle p_a, t_triangle p_b);
int 			is_triangle_in_triangle(t_triangle p_a, t_triangle p_b);

int				old_intersect(t_triangle p_triangle, t_vector4 p_normal, t_line line, t_vector4 *intersection);
int				is_same_sign(float a, float b);
int				is_mid(float min, float max, float value);

#endif
