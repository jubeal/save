/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubeal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 15:20:08 by jubeal            #+#    #+#             */
/*   Updated: 2019/01/18 16:39:29 by jubeal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	translate(t_fract *first, int key)
{
	if (key == 126)
		first->tools->y -= 10;
	if (key == 125)
		first->tools->y += 10;
	if (key == 124)
		first->tools->x += 10;
	if (key == 123)
		first->tools->x -= 10;
	ft_bzero(first->data, first->win_x * first->win_y * 4);
	fractol(first);
}

int		zoom(int key, t_fract *first)
{
	if (key == 78 || key == 4)
	{
		first->tools->x /= 1.2;
		first->tools->y /= 1.2;
		first->tools->zoomx /= 1.2;
		first->tools->zoomy /= 1.2;
		first->tools->x -= first->win_x / 12;
		first->tools->y -= first->win_y / 12;
		first->tools->iter_max -= 3;
		ft_bzero(first->data, first->win_x * first->win_y * 4);
		fractol(first);
	}
	if (key == 69 || key == 5)
	{
		first->tools->x += first->win_x / 12;
		first->tools->y += first->win_y / 12;
		first->tools->x *= 1.2;
		first->tools->y *= 1.2;
		first->tools->zoomx *= 1.2;
		first->tools->zoomy *= 1.2;
		first->tools->iter_max += 3;
		ft_bzero(first->data, first->win_x * first->win_y * 4);
		fractol(first);
	}
	return (1);
}

int		mouse_move_hook(int x, int y, t_fract *first)
{
	if (x < 0 || x >= first->win_x || y < 0 || y < 0 || y >= first->win_y ||
			first->tools->mouse_stop == 1)
		return (0);
	first->tools->mouse_x = x;
	first->tools->mouse_y = y;
	ft_bzero(first->data, first->win_x * first->win_y * 4);
	fractol(first);
	return (1);
}

void	end_program(t_fract *first)
{
	first->i++;
	free(first->tools);
	first->tools = NULL;
	if (first->av[first->i])
	{
		fractol_choice(first);
		ft_bzero(first->data, first->win_x * first->win_y * 4);
		fractol(first);
	}
	else
	{
		mlx_destroy_image(first->ptr, first->img);
		mlx_destroy_window(first->ptr, first->win);
		free(first);
		exit(0);
	}
}
