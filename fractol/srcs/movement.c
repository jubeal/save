/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubeal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 15:20:08 by jubeal            #+#    #+#             */
/*   Updated: 2019/01/10 16:57:44 by jubeal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	translate(t_fract *first, int key)
{
	if (key == 126)
	{
		first->tools->y1 -= 0.01;
		first->tools->y2 -= 0.01;
	}
	if (key == 125)
	{
		first->tools->y1 += 0.01;
		first->tools->y2 += 0.01;
	}
	if (key == 124)
	{
		first->tools->x1 += 0.01;
		first->tools->x2 += 0.01;
	}
	if (key == 123)
	{
		first->tools->x1 -= 0.01;
		first->tools->x2 -= 0.01;
	}
	ft_bzero(first->data, WIN_X * WIN_Y * 4);
	Mandelbrot(first);
}

void	zoom(t_fract *first, int key)
{
	if (key == 78)
	{
		first->tools->x1 *= 1.1;
		first->tools->x2 /= 1.2;
		first->tools->y1 *= 1.2;
		first->tools->y2 /= 1.2;
		first->tools->iter_max /= 1.2;
	}
	if (key == 69)
	{
		first->tools->x1 /= 1.2;
		first->tools->x2 *= 1.2;
		first->tools->y1 /= 1.2;
		first->tools->y2 *= 1.2;
		first->tools->iter_max *= 1.2;
	}
	ft_bzero(first->data, WIN_X * WIN_Y * 4);
	Mandelbrot(first);
}
