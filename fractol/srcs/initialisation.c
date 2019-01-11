/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubeal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 15:23:43 by jubeal            #+#    #+#             */
/*   Updated: 2019/01/11 14:51:20 by jubeal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		init_fract(t_fract **first)
{
	t_fract	*tmp;

	tmp = *first;
	if (!tmp)
	{
		if (!(tmp = (t_fract *)malloc(sizeof(t_fract))))
			return (0);
		*first = tmp;
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		if (!(tmp->next = (t_fract *)malloc(sizeof(t_fract))))
			return (0);
		tmp = tmp->next;
	}
	tmp->win_x = 540;
	tmp->win_y = 480;
	tmp->ptr = NULL;
	tmp->win = NULL;
	tmp->img = NULL;
	tmp->data = NULL;
	tmp->next = NULL;
	tmp->tools = NULL;
	tmp->color_value = 3;
	tmp->r = 5;
	tmp->g = 10;
	tmp->b = 2;
	return (1);
}

void	open_windows(t_fract *first)
{
	void	*ptr;
	void	*win;

	if (!(ptr = mlx_init()))
	{
		ft_putstr("manque de place pour mlx_init\n");
		exit(0);
	}
	win = mlx_new_window(ptr, first->win_x, first->win_y, "fractol");
	first->ptr = ptr;
	first->win = win;
	if (!(first->img = mlx_new_image(ptr, first->win_x, first->win_y)))
	{
		ft_putstr("manque de place pour new_image\n");
		exit(0);
	}
	if (!(first->data = mlx_get_data_addr(first->img, &first->bpp,
					&first->size_line, &first->endian)))
	{
		ft_putstr("manque de place pour data_addr\n");
		exit(0);
	}
}

void	pixel_put_img(int x, int y, t_fract *curent, int color)
{
	int		pixel;

	pixel = x * 4 + y * curent->size_line;
	if (pixel < 0 || pixel > curent->win_x * curent->win_y * 4)
		return ;
	curent->data[pixel] = color & 0xFF;
	curent->data[pixel + 1] = color >> 8 & 0xFF;
	curent->data[pixel + 2] = color >> 16 & 0xFF;
}

int		set_color(t_maths *tools, t_fract *first)
{
	return (((255 - (tools->i * first->r) * first->color_value) << 16) +
			((255 - (tools->i * first->g) * first->color_value) << 8) +
			((tools->i * first->b) * first->color_value));
}

void	init_maths(t_maths **tools, t_fract *first)
{
	if (!(*tools = (t_maths *)malloc(sizeof(t_maths))))
	{
		ft_putstr("manque de place pour t_maths\n");
		exit(0);
	}
	(*tools)->iter_max = 50;
	(*tools)->cr = 0;
	(*tools)->ci = 0;
	(*tools)->zr = 0;
	(*tools)->zi = 0;
	(*tools)->i = 0;
	(*tools)->x = 0;
	(*tools)->y = 0;
	(*tools)->x1 = -2.1;
	(*tools)->x2 = 0.6;
	(*tools)->y1 = -1.2;
	(*tools)->y2 = 1.2;
	(*tools)->zoomx = first->win_x / (first->tools->x2 - first->tools->x1);
	(*tools)->zoomy = first->win_y / (first->tools->y2 - first->tools->y1);
}
