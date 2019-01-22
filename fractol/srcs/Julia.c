/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubeal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 14:21:09 by jubeal            #+#    #+#             */
/*   Updated: 2019/01/22 21:21:56 by jubeal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	calcul(t_fract *first, int x, int y)
{
	long double tmp;

	first->tools->cr = 0.285;
	first->tools->ci = 0.01;
	first->tools->zr = (long double)x / first->tools->zoomx +
	first->tools->x1;
	first->tools->zi = (long double)y / first->tools->zoomy +
		first->tools->y1;
	first->tools->i = 0;
	while (first->tools->zr * first->tools->zr + first->tools->zi *
		first->tools->zi < 4 && first->tools->i <
		first->tools->iter_max)
	{
		tmp = first->tools->zr;
		first->tools->zr = first->tools->zr * first->tools->zr -
		first->tools->zi * first->tools->zi + first->tools->cr +
			((double)first->tools->mouse_x / first->win_x);
		first->tools->zi = 2 * first->tools->zi * tmp + first->tools->ci +
			((double)first->tools->mouse_y / first->win_y);
		first->tools->i++;
	}
	if (first->tools->i != first->tools->iter_max)
		pixel_put_img(x - first->tools->x, y - first->tools->y, first,
				set_color(first->tools, first));
}

static void	*pixel_choice(void *data)
{
	int			x;
	int			y;
	int			part;
	t_thread	*threads;

	threads = (t_thread *)data;
	part = threads->first->win_y / 8;
	y = part * threads->idx + threads->first->tools->y;
	while (y < part * (threads->idx + 1) + threads->first->tools->y)
	{
		x = threads->first->tools->x;
		while (x < threads->first->win_x + threads->first->tools->x)
		{
			calcul(threads->first, x, y);
			x++;
		}
		y++;
	}
	pthread_exit(NULL);
}

void		julia(t_fract *first)
{
	int			idx;
	t_thread	**threads;

	if (!first->tools)
	{
		init_maths(&first->tools, first);
		first->tools->x1 = -1.3;
		first->tools->x2 = 0.7;
		first->tools->y1 = -1.2;
		first->tools->y2 = 1.2;
		first->tools->iter_max = 150;
	}
	if (!(threads = (t_thread **)malloc(sizeof(t_thread *) * 8)))
		return ;
	idx = -1;
	while (++idx < 8)
	{
		if (!(threads[idx] = (t_thread *)malloc(sizeof(t_thread))))
			return ;
		threads[idx]->first = first;
		threads[idx]->idx = idx;
		if ((pthread_create(&threads[idx]->thread, NULL, pixel_choice,
						threads[idx])) == -1)
			return ;
	}
	idx = -1;
	while (++idx < 8)
	{
		if (pthread_join(threads[idx]->thread, NULL))
			return ;
		free(threads[idx]);
	}
	mlx_put_image_to_window(first->ptr, first->win, first->img, 0, 0);
}
