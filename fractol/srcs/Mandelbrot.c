/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubeal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 15:13:05 by jubeal            #+#    #+#             */
/*   Updated: 2019/01/22 21:16:34 by jubeal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	calcul(t_fract *first, int x, int y)
{
	long double tmp;

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
			first->tools->zi * first->tools->zi + first->tools->cr;
		first->tools->zi = 2 * first->tools->zi * tmp + first->tools->ci;
		first->tools->i++;
	}
	if (first->tools->i != first->tools->iter_max)
		pixel_put_img(x - first->tools->x, y - first->tools->y, first,
			set_color(first->tools, first));
}

void		mandelbrot(t_fract *first)
{
	int			x;
	int			y;

	if (!first->tools)
		init_maths(&first->tools, first);
	y = first->tools->y;
	while (y < first->win_y + first->tools->y)
	{
		x = first->tools->x;
		while (x < first->win_x + first->tools->x)
		{
			calcul(first, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(first->ptr, first->win, first->img, 0, 0);
}
