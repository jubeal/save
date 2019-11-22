/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjouber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 12:07:36 by adjouber          #+#    #+#             */
/*   Updated: 2019/10/31 12:07:40 by adjouber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unknow_project.h"

static void			calc_value(t_vector2 *error, t_vector2 *income,
						t_vector2_int start, t_vector2_int end)
{
	error->x = end.x - start.x;
	error->y = end.y - start.y;
	income->x = (error->x >= 0) ? 1 : -1;
	income->y = (error->y >= 0) ? 1 : -1;
	error->x = (error->x >= 0) ? error->x : -error->x;
	error->y = (error->y >= 0) ? error->y : -error->y;
}

static void			calc_line_x_major(t_vector2_int_list *result,
					t_vector2 *error, t_vector2 *income, t_vector2_int start)
{
	int cumul;
	int	j;

	j = 1;
	cumul = error->x / 2;
	while (j <= error->x)
	{
		start.x += income->x;
		cumul += error->y;
		if (cumul >= error->x)
		{
			cumul -= error->x;
			start.y += income->y;
		}
		t_vector2_int_list_push_back(result, start);
		j++;
	}
}

static void			calc_line_y_major(t_vector2_int_list *result,
					t_vector2 *error, t_vector2 *income, t_vector2_int start)
{
	int cumul;
	int	j;

	j = 1;
	cumul = error->y / 2;
	while (j <= error->y)
	{
		start.y += income->y;
		cumul += error->x;
		if (cumul >= error->y)
		{
			cumul -= error->y;
			start.x += income->x;
		}
		t_vector2_int_list_push_back(result, start);
		j++;
	}
}

t_vector2_int_list	calc_line(t_vector2_int start, t_vector2_int end)
{
	t_vector2_int_list	result;
	t_vector2			error;
	t_vector2			income;

	calc_value(&error, &income, start, end);
	result = create_t_vector2_int_list(start);
	if (error.x >= error.y)
		calc_line_x_major(&result, &error, &income, start);
	else
		calc_line_y_major(&result, &error, &income, start);
	return (result);
}
