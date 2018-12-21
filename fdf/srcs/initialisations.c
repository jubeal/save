/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubeal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 15:12:33 by jubeal            #+#    #+#             */
/*   Updated: 2018/12/21 14:33:19 by jubeal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		init_t_map(t_map **map)
{
	if (!(*map = (t_map *)malloc(sizeof(t_map))))
		return (0);
	(*map)->x_max = 0;
	(*map)->y_max = -1;
	(*map)->z_max = 0;
	(*map)->ptr = NULL;
	(*map)->win = NULL;
	(*map)->first = NULL;
	(*map)->last = NULL;
	(*map)->zoomx = 0;
	(*map)->zoomy = 0;
	if (!((*map)->curent = init_t_color()))
		return (0);
	(*map)->affichage = 0;
	(*map)->img = NULL;
	(*map)->data = NULL;
	(*map)->bpp = 0;
	(*map)->size_line = 0;
	(*map)->endian = 0;
	return (1);
}

void	init_points(t_point **points, t_map *map)
{
	t_point	*tmp;

	tmp = *points;
	while (tmp->next)
		tmp = tmp->next;
	map->last = tmp;
	map->first = *points;
	map->zoomx = (WIN_X * 0.4) / map->x_max + 1;
	map->zoomy = (WIN_Y * 0.4) / map->y_max + 1;
	map->zoomz = 0;
}
