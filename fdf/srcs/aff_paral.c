/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_paral.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubeal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 12:29:48 by jubeal            #+#    #+#             */
/*   Updated: 2018/12/19 16:23:46 by jubeal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_paral(t_map *map)
{
	t_point *tmp;
	int		x;
	int		y;

	tmp = map->first;
	while (tmp)
	{
		x = tmp->x * map->zoomx;
		y = tmp->y * map->zoomy;
		tmp->truex = x + (WIN_X / 3.5);
		tmp->truey = (y - tmp->z * map->zoomz) + (WIN_Y / 4);
		tmp->colorchange1 = (y - ((tmp->z * map->zoomz) * 0.3)) + (WIN_Y / 10);
		tmp->colorchange2 = (y - ((tmp->z * map->zoomz) * 0.6)) + (WIN_Y / 10);
		tmp = tmp->next;
	}
	map->affichage = 1;
	draw_wires(map);
}

void	change_aff(t_map *map)
{
	mlx_clear_window(map->ptr, map->win);
	if (map->affichage == 0)
		draw_paral(map);
	else
		rotation_points(map);
}
