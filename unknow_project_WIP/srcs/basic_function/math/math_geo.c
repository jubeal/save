/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_geo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboutin <gboutin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 17:05:09 by adjouber          #+#    #+#             */
/*   Updated: 2019/11/22 10:18:58 by gboutin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unknow_project.h"

int				same_side(t_vector4 p1, t_vector4 p2, t_vector4 a, t_vector4 b)
{
	t_vector4	cp1;
	t_vector4	cp2;
	t_vector4	b_a;

	b_a = substract_vector4_to_vector4(b, a);
	cp1 = cross_t_vector4(b_a, substract_vector4_to_vector4(p1, a));
	cp2 = cross_t_vector4(b_a, substract_vector4_to_vector4(p2, a));
	if (dot_t_vector4(cp1, cp2) >= 0)
		return (BOOL_TRUE);
	else
		return (BOOL_FALSE);
}

t_vector4		intersect_plane_by_line(t_vector4 p_normal, t_vector4 p_center,
											t_vector4 start, t_vector4 end)
{
	t_vector4	intersection;
	t_vector4	basic_line;
	t_vector4	normalized_plane;
	float		tabf[4];

	normalized_plane = normalize_t_vector4(p_normal);
	tabf[0] = dot_t_vector4(normalized_plane, p_center);
	tabf[1] = dot_t_vector4(start, normalized_plane);
	tabf[2] = dot_t_vector4(end, normalized_plane);
	tabf[3] = (tabf[0] - tabf[1]) / (tabf[2] - tabf[1]);
	basic_line = substract_vector4_to_vector4(end, start);
	intersection = mult_vector4_by_float(basic_line, tabf[3]);
	return (add_vector4_to_vector4(start, intersection));
}

int				is_point_on_line(t_vector4 a, t_vector4 b, t_vector4 c)
{
	float dist_tot;
	float dist_part_one;
	float dist_part_two;

	dist_tot = calc_dist_vector4_to_vector4(a, b);
	dist_part_one = calc_dist_vector4_to_vector4(a, c);
	dist_part_two = calc_dist_vector4_to_vector4(c, b);
	if (dist_tot == dist_part_one + dist_part_two)
		return (BOOL_TRUE);
	return (BOOL_FALSE);
}

float			calc_distance_to_plane(t_vector4 p_normal, t_vector4 p_center,
														t_vector4 p_point)
{
	t_vector4	normalized_plane;
	float		result;

	normalized_plane = normalize_t_vector4(p_normal);
	result = p_point.x * normalized_plane.x
			+ p_point.y * normalized_plane.y
			+ p_point.z * normalized_plane.z
			- dot_t_vector4(normalized_plane, p_center);
	return (result);
}

t_vector4		interpolate_vector4_over_line(float ratio_x, float ratio_y,
													t_vector4 ua, t_vector4 ub)
{
	t_vector4	result;

	result.x = ((ub.x - ua.x) * ratio_x) + ua.x;
	result.y = ((ub.y - ua.y) * ratio_y) + ua.y;
	result.z = 0;
	return (result);
}
