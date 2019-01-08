/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubeal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 15:13:05 by jubeal            #+#    #+#             */
/*   Updated: 2019/01/08 17:34:58 by jubeal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	Mandelbrot(t_fract *first)
{
	t_maths	*tools;
	int		tmp;

	tools = NULL;
	init_maths(&tools);
	tools->zoomx = WIN_X / (tools->x2 - tools->x1);
	tools->zoomy = WIN_Y / (tools->y2 - tools->y1);
	while (first->y < WIN_Y)
	{
		while (first->x < WIN_X)
		{
			tools->cr = (long double)first->x / tools->zoomx + tools->x1;
			tools->ci = (long double)first->y / tools->zoomy + tools->y1;
			tools->zr = 0;
			tools->zi = 0;
			tools->i = 0;
			while (tools->zr * tools->zr + tools->zi * tools->zi < 4
					&& tools->i < tools->iter_max)
			{
				tmp = tools->zr;
				tools->zr = tools->zr * tools->zr - tools->zi * tools->zi
					+ tools->cr;
				tools->zi = 2 * tools->zi * tmp + tools->ci;
				tools->i++;
			}
			if (tools->i == tools->iter_max)
			{
				pixel_put_img(first->x, first->y, first, 0xFFFFFF);
			}
			first->x++;
		}
		first->x = 0;
		first->y++;
	}
	mlx_put_image_to_window(first->ptr, first->win, first->img, 0, 0);
}
