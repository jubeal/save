/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_vector.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboutin <gboutin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 16:34:22 by adjouber          #+#    #+#             */
/*   Updated: 2019/11/22 10:18:59 by gboutin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unknow_project.h"

t_vector4		cross_t_vector4(t_vector4 a, t_vector4 b)
{
	t_vector4	result;

	result = create_t_vector4(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z,
								a.x * b.y - a.y * b.x);
	return (result);
}

t_vector4		normalize_t_vector4(t_vector4 v)
{
	float		length_of_v;

	length_of_v = sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
	return (create_t_vector4(v.x / length_of_v, v.y
							/ length_of_v, v.z / length_of_v));
}

float			dot_t_vector4(t_vector4 a, t_vector4 b)
{
	float		result;

	result = a.x * b.x + a.y * b.y + a.z * b.z;
	return (result);
}

float			edge_t_vector4(t_vector4 a, t_vector4 b, t_vector4 c)
{
	float		result;

	result = (c.x - a.x) * (b.y - a.y) - (c.y - a.y) * (b.x - a.x);
	return (result);
}

float			calc_dist_vector4_to_vector4(t_vector4 a, t_vector4 b)
{
	return (sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y)
		+ (b.z - a.z) * (b.z - a.z)));
}
