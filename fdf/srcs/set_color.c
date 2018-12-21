/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubeal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 13:10:02 by jubeal            #+#    #+#             */
/*   Updated: 2018/12/21 18:03:42 by jubeal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_color		*init_t_color()
{
	t_color	*ret;
	t_color *tmp;

	if (!(ret = (t_color *)malloc(sizeof(t_color))))
		return (NULL);
	ret->color = 0x00CC00;
	ret->color1 = 0x994C00;
	ret->color2 = 0xFFFFFF;
	if (!(ret->next = (t_color *)malloc(sizeof(t_color))))
		return (NULL);
	tmp = ret->next;
	tmp->color = 0xFFFFFF;
	tmp->color1 = 0xFF9A00;
	tmp->color2 = 0xFF00A2;
	tmp->next = ret;
	return (ret);
}

void		change_color(t_map *map)
{
	map->curent = map->curent->next;
	if (map->affichage)
		draw_paral(map);
	else
		rotation_points(map);
}

static int	color_degraded(int color_from, int color_to, int place, int max)
{
	int		R;
	int		G;
	int		B;
	int		i;

	R = (color_from & 0xFF0000) >> 16;
	G = (color_from & 0x00FF00) >> 8;
	B = color_from & 0x0000FF;
	i = 0;
	while (++i < place)
	{
		R += ((color_from >> 16 & 0xFF) - (color_from >> 16 & 0xFF)) / max;
		G += ((color_to >> 8 & 0xFF) - (color_from >> 8 & 0xFF)) / max;
		B += ((color_to & 0xFF) - (color_from & 0xFF)) / max;
	}
	R = R << 16;
	G = G << 8;
	return (R + G + B);
}

int			color_set(t_point *to, t_point *from, t_map *map, int place)
{
	int		xory;
	int		xory2;

	xory = to->truex - from->truex > to->truey - from->truey ?
		to->truex - from->truex : to->truey - from->truey;
	xory2 = to->truex - from->truex > to->truey - from->truey ?
		from->truex : from->truey;
	if (from->z > (map->z_max / 2) && to->z > (map->z_max / 2)
			&& map->zoomz > 0)
		return (map->curent->color2);
	if (from->z > 0 && to->z > 0 && map->zoomz > 0)
		return (map->curent->color1);
	if (from->z == 0 && to->z > (map->z_max / 2) && map->zoomz > 0)
		return (color_degraded(map->curent->color, map->curent->color2,
					place - xory2, xory));
	return (map->curent->color);
}
