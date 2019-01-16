/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubeal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 15:20:08 by jubeal            #+#    #+#             */
/*   Updated: 2019/01/11 14:04:24 by jubeal           ###   ########.fr       */
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

void	zoom(t_fract *first, int key)
{
	if (key == 69)
	{
		first->tools->x /= 1.2;
		first->tools->y /= 1.2;
		first->tools->zoomx /= 1.2;
		first->tools->zoomy /= 1.2;
		first->tools->x -= first->win_x / 12;
		first->tools->y -= first->win_y / 12;
		first->tools->iter_max -= 3;
	}
	if (key == 78)
	{
		first->tools->x += first->win_x / 12;
		first->tools->y += first->win_y / 12;
		first->tools->x *= 1.2;
		first->tools->y *= 1.2;
		first->tools->zoomx *= 1.2;
		first->tools->zoomy *= 1.2;
		first->tools->iter_max += 3;
	}
	ft_bzero(first->data, first->win_x * first->win_y * 4);
	fractol(first);
}
