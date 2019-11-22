/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjouber <adjouber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 15:50:12 by adjouber          #+#    #+#             */
/*   Updated: 2019/10/31 16:38:00 by adjouber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unknow_project.h"

float			get_short_float(float a, float b, float c)
{
	float			result;

	result = a;
	if (result > b)
		result = b;
	if (result > c)
		result = c;
	return (result);
}

float			get_big_float(float a, float b, float c)
{
	float			result;

	result = a;
	if (result < b)
		result = b;
	if (result < c)
		result = c;
	return (result);
}

float			float_min(float a, float b)
{
	if (a <= b)
		return (a);
	return (b);
}

float			float_max(float a, float b)
{
	if (a >= b)
		return (a);
	return (b);
}

float			ft_abs_float(float src)
{
	if (src < 0)
		return (-src);
	return (src);
}
