/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_paral.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubeal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 12:29:48 by jubeal            #+#    #+#             */
/*   Updated: 2018/12/21 17:35:14 by jubeal           ###   ########.fr       */
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
		tmp->truex = x + map->merge_x;;
		tmp->truey = (y - tmp->z * map->zoomz) + map->merge_y;
		tmp = tmp->next;
	}
	map->affichage = 1;
	draw_wires(map);
}

void	change_aff(t_map *map)
{
	ft_bzero(map->data, WIN_X * WIN_Y * 4);
	if (map->affichage == 0)
		draw_paral(map);
	else
		rotation_points(map);
}
