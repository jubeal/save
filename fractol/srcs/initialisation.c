/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubeal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 15:23:43 by jubeal            #+#    #+#             */
/*   Updated: 2019/01/07 16:43:05 by jubeal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init_fract(t_fract **first)
{
	t_fract	*tmp;

	tmp = *first;
	if (!tmp)
	{
		if (!(tmp = (t_fract *)malloc(sizeof(t_fract))))
			return (0);
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		if (!(tmp->next = (t_fract *)malloc(sizeof(t_fract))))
			return (0);
		tmp = tmp->next;
	}
	tmp->x = 0;
	tmp->y = 0;
	tmp->ptr = NULL;
	tmp->win = NULL;
	tmp->img = NULL;
	tmp->data = NULL;
	tmp->next = NULL;
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
	win = mlx_new_window(ptr, WIN_X, WIN_Y, "fractol");
	first->ptr = ptr;
	first->win = win;
	if (!(map->img = mlx_new_image(ptr, WIN_X, WIN_Y)))
	{
		ft_putstr("manque de place pour new_image\n");
		exit(0);
	}
	if (!(map->data = mlx_get_data_addr(map->img, &map->bpp, &map->size_line,
					&map->endian)))
	{
		ft_putstr("manque de place pour data_addr\n");
		exit(0);
	}
}

void	pixel_put_img(int x, int y, t_fract curent, int color)
{
	int		pixel;

	pixel = x * 4 + y * curent->size_line;
	if (pixel < 0 || pixel > WIN_X * WIN_Y * 4)
		return ;
	curent->data[pixel] = color & 0xFF;
	curent->data[pixel + 1] = color >> 8 & 0xFF;
	curent->data[pixel + 2] = color >> 16 & 0xFF;
}
