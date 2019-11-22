/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjouber <adjouber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 17:00:32 by adjouber          #+#    #+#             */
/*   Updated: 2019/10/31 17:08:51 by adjouber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unknow_project.h"

int		is_mid(float min, float max, float value)
{
	if (value >= min && value <= max)
		return (BOOL_TRUE);
	return (BOOL_FALSE);
}

float	clamp_float_value(float min, float value, float max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}

int		clamp_int_value(int min, int value, int max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}

float	interpolate_ratio(float a, float b, float c)
{
	if (b - a == 0)
		return (0);
	return ((c - a) / (b - a));
}

int		is_same_sign(float a, float b)
{
	if (a < 0)
	{
		if (b < 0)
			return (BOOL_TRUE);
		else
			return (BOOL_FALSE);
	}
	else
	{
		if (b >= 0)
			return (BOOL_TRUE);
		else
			return (BOOL_FALSE);
	}
}
