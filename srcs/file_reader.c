/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_reader.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubeal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 13:34:32 by jubeal            #+#    #+#             */
/*   Updated: 2018/12/04 15:38:08 by jubeal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		file_reader(int fd, t_point *points, t_map *map)
{
	char	*line;
	char	**line_split;
	int		x;
	t_point	*tmp;

	if (!(map = (t_map *)malloc(sizeof(t_map))))
		return (0);
	map->y_max = 0;
	tmp = points
	while (get_next_line(fd, &line) > 0)
	{
		x = -1;
		line_split = ft_strsplit(line, ' ');
		while (line_split[++x])
		{
			if (!(tmp = (t_point *)malloc(sizeof(t_point))))	
				return (0);
			tmp->valeur = ft_atoi(line_split[x]);
			tmp->x = x - 1;
		}
		map->y_max++;
	}
}
