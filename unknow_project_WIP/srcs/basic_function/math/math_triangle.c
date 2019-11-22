/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_triangle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboutin <gboutin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 16:57:24 by adjouber          #+#    #+#             */
/*   Updated: 2019/11/22 10:18:59 by gboutin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unknow_project.h"

int		is_triangle_parallele(t_triangle p_a, t_triangle p_b)
{
	t_vector4	normal_a;
	t_vector4	normal_b;
	float		dot;

	normal_a = cross_t_vector4(substract_vector4_to_vector4(p_a.b, p_a.a),
			substract_vector4_to_vector4(p_a.c, p_a.a));
	normal_b = cross_t_vector4(substract_vector4_to_vector4(p_b.b, p_b.a),
			substract_vector4_to_vector4(p_b.c, p_b.a));
	dot = dot_t_vector4(normal_a, normal_b);
	if (dot == 1 || dot == -1)
		return (BOOL_TRUE);
	return (BOOL_FALSE);
}

int		intersect_triangle_by_segment(t_triangle p_triangle, t_vector4 p_normal,
										t_line line, t_vector4 *intersection)
{
	if (dot_t_vector4(p_normal,
		normalize_t_vector4(substract_vector4_to_vector4(line.b, line.a))) == 0)
		return (BOOL_ERROR);
	*intersection = intersect_plane_by_line(p_normal, p_triangle.a,
													line.a, line.b);
	if (is_point_on_line(line.a, line.b, *intersection) == BOOL_FALSE)
		return (BOOL_FALSE);
	if (is_point_on_triangle(p_triangle, *intersection) == BOOL_FALSE)
		return (BOOL_FALSE);
	return (BOOL_TRUE);
}

int		is_point_on_triangle(t_triangle a, t_vector4 point)
{
	if (same_side(point, a.a, a.b, a.c) == BOOL_TRUE
		&& same_side(point, a.b, a.c, a.a) == BOOL_TRUE
		&& same_side(point, a.c, a.a, a.b) == BOOL_TRUE)
		return (BOOL_TRUE);
	else
		return (BOOL_FALSE);
}

float	calc_distance_to_triangle(t_triangle p_triangle, t_vector4 point)
{
	float		sb;
	float		sn;
	float		sd;
	t_vector4	normal;

	normal = cross_t_vector4(substract_vector4_to_vector4(p_triangle.b,
				p_triangle.a), substract_vector4_to_vector4(p_triangle.c,
														p_triangle.a));
	sn = -dot_t_vector4(normal,
			substract_vector4_to_vector4(point, p_triangle.a));
	sd = dot_t_vector4(normal, normal);
	sb = sn / sd;
	return (sb);
}

int		is_triangle_in_triangle(t_triangle p_a, t_triangle p_b)
{
	if (is_triangle_parallele(p_a, p_b) == BOOL_FALSE)
		return (BOOL_FALSE);
	if (calc_distance_to_triangle(p_a, p_b.a) != 0)
		return (BOOL_FALSE);
	if (is_point_on_triangle(p_a, p_b.a) == BOOL_TRUE ||
		is_point_on_triangle(p_a, p_b.b) == BOOL_TRUE ||
		is_point_on_triangle(p_a, p_b.c) == BOOL_TRUE)
		return (BOOL_TRUE);
	if (is_point_on_triangle(p_b, p_a.a) == BOOL_TRUE ||
		is_point_on_triangle(p_b, p_a.b) == BOOL_TRUE ||
		is_point_on_triangle(p_b, p_a.c) == BOOL_TRUE)
		return (BOOL_TRUE);
	return (BOOL_FALSE);
}
