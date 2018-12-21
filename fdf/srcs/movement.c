/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubeal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 13:53:44 by jubeal            #+#    #+#             */
/*   Updated: 2018/12/21 17:28:22 by jubeal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		rotation_points(t_map *map)
{
	t_point	*tmp;
	float	phi;
	int		x;
	int		y;
	int		z;

	tmp = map->first;
	phi = 0.55;
	while (tmp)
	{
		x = (tmp->x * map->zoomx * cos(phi)) + (tmp->y * map->zoomy
				* -sin(phi));
		y = (tmp->x * map->zoomx * sin(phi)) + (tmp->y * map->zoomy * cos(phi));
		z = tmp->z * 1;
		tmp->truex = x + map->merge_x;
		tmp->z = z;
		tmp->truey = (y - z * map->zoomz) + map->merge_y;
		if (map->z_max < tmp->z)
			map->z_max = tmp->z;
		tmp = tmp->next;
	}
	map->affichage = 0;
	draw_wires(map);
}

void		translate_points(t_map *map, int direction)
{
	int		directionx;
	int		directiony;
	t_point	*tmp;

	tmp = map->first;
	directionx = 0;
	directiony = 0;
	ft_bzero(map->data, WIN_X * WIN_Y * 4);
	if (direction == 125)
		directiony -= 5;
	if (direction == 126)
		directiony += 5;
	if (direction == 123)
		directionx += 5;
	if (direction == 124)
		directionx -= 5;
	map->merge_x += directionx;
	map->merge_y += directiony;
	if (map->affichage)
		draw_paral(map);
	else
		rotation_points(map);
}

void		zoom_points(t_map *map, int direction)
{
	ft_bzero(map->data, WIN_X * WIN_Y * 4);
	if (direction == 69)
	{
		map->zoomx += 5;
		map->zoomy += 5;
		if (map->affichage)
			draw_paral(map);
		else
			rotation_points(map);
		return ;
	}
	map->zoomx -= 5;
	map->zoomy -= 5;
	if (map->affichage)
		draw_paral(map);
	else
		rotation_points(map);
}

void		heigth_difference(t_map *map, int direction)
{
	ft_bzero(map->data, WIN_X * WIN_Y * 4);
	if (direction == 27)
		map->zoomz -= 1;
	else
		map->zoomz += 1;
	if (map->affichage)
		draw_paral(map);
	else
		rotation_points(map);
}
