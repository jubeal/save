/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubeal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 15:20:46 by jubeal            #+#    #+#             */
/*   Updated: 2019/01/24 14:30:46 by jubeal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	mouse_translate(int x2, int y2, t_fract *first)
{
	if (first->trans_stop == 0)
		return (0);
	first->tools->x += (x2 - first->trans_x) / 4;
	first->tools->y += (y2 - first->trans_y) / 4;
	ft_bzero(first->data, first->win_x * first->win_y * 4);
	fractol(first);
	return (0);
}

int			mouse_key(int key, int x, int y, t_fract *first)
{
	if (key == 4 || key == 5)
		zoom(key, first);
	if (key == 1 && x >= 0 && y >= 0)
	{
		first->trans_stop != 0 ? first->trans_stop = 0 : first->trans_stop++;
		first->trans_x = x;
		first->trans_y = y;
		mlx_hook(first->win, 6, (1L << 6), mouse_translate, first);
	}
	return (0);
}
