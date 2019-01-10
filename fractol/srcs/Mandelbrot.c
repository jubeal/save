/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubeal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 15:13:05 by jubeal            #+#    #+#             */
/*   Updated: 2019/01/10 16:41:40 by jubeal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	Mandelbrot(t_fract *first)
{
	long double	tmp;
	int			x;
	int			y;

	if (!first->tools)
		init_maths(&first->tools);
	first->tools->zoomx = WIN_X / (first->tools->x2 - first->tools->x1);
	first->tools->zoomy = WIN_Y / (first->tools->y2 - first->tools->y1);
	y = 0;
	while (y < WIN_Y)
	{
		x = 0;
		while (x < WIN_X)
		{
			first->tools->cr = (long double)x / first->tools->zoomx +
				first->tools->x1;
			first->tools->ci = (long double)y / first->tools->zoomy +
				first->tools->y1;
			first->tools->zr = 0;
			first->tools->zi = 0;
			first->tools->i = 0;
			while (first->tools->zr * first->tools->zr + first->tools->zi *
					first->tools->zi < 4 && first->tools->i <
					first->tools->iter_max)
			{
				tmp = first->tools->zr;
				first->tools->zr = first->tools->zr * first->tools->zr -
					first->tools->zi * first->tools->zi+ first->tools->cr;
				first->tools->zi = 2 * first->tools->zi * tmp + first->tools->ci;
				first->tools->i++;
			}
			if (first->tools->i != first->tools->iter_max)
				pixel_put_img(x, y, first, set_color(first->tools, first));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(first->ptr, first->win, first->img, 0, 0);
}
