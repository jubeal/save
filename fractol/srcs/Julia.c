/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubeal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 14:21:09 by jubeal            #+#    #+#             */
/*   Updated: 2019/01/11 15:17:05 by jubeal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	Julia(t_fract *first)
{
	long double	tmp;
	int			x;
	int			y;

	if (!first->tools)
	{
		init_maths(&first->tools, first);
		first->tools->x1 = -1;
		first->tools->x2 = 1;
		first->tools->y1 = -1.2;
		first->tools->y2 = 1.2;
		first->tools->iter_max = 150;
	}
	y = first->tools->y;
	while (y < first->win_y + first->tools->y)
	{
		x = first->tools->x;
		while (x < first->win_x + first->tools->x)
		{
			first->tools->cr = 0.285;
			first->tools->ci = 0.01;
			first->tools->zr = (long double)x / first->tools->zoomx +
				first->tools->x1;
			first->tools->zr = (long double)x / first->tools->zoomy +
				first->tools->y1;
			first->tools->i = 0;
			while (first->tools->zr * first->tools->zr + first->tools->zi *
					first->tools->zi < 4 && first->tools->i <
					first->tools->iter_max)
			{
				tmp = first->tools->zr;
				first->tools->zr = first->tools->zr * first->tools->zr -
					first->tools->zi * first->tools->zi + first->tools->cr;
				first->tools->zi = 2 * first->tools->zi * tmp + first->tools->ci;
				first->tools->i++;
			}
			if (first->tools->i != first->tools->iter_max)
				pixel_put_img(x - first->tools->x, y - first->tools->y, first,
						set_color(first->tools, first));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(first->ptr, first->win, first->img, 0, 0);
}
